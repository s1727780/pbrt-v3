
/*
    pbrt source code is Copyright(c) 1998-2016
                        Matt Pharr, Greg Humphreys, and Wenzel Jakob.

    This file is part of pbrt.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */


// shapes/displacedsphere.cpp*
#include "shapes/displacedsphere.h"
#include "sampling.h"
#include "paramset.h"
#include "efloat.h"
#include "stats.h"

#include "imageio.h"
#include "stats.h"

namespace pbrt {

// Sphere Method Definitions
Bounds3f DispSphere::ObjectBound() const {
    return Bounds3f(Point3f(-dispRadius, -dispRadius, zMin),
                    Point3f(dispRadius, dispRadius, zMax));
}

bool DispSphere::Intersect(const Ray &r, Float *tHit, SurfaceInteraction *isect,
                       bool testAlphaTexture) const {
    
    // Check intersect at dispRadius
    bool hitDispRadius = hasIntersectedSphere(r, tHit, isect, testAlphaTexture, dispRadius);
    if (!hitDispRadius) return false;

    else {
        bool hit;
        Point2f pos2f;
        Vector3f normal;
        float parallaxRadius;
        Float disp;
        int pos;

        Float disp1, disp2, disp3, disp4;
        float x, y, du1, dv1;
        float a, b, val;

        float c, d, duVal, dvVal;


        


        // Parallax Mapping Algorithm
        for (int layer = parallaxLayers; layer >= 0; layer--){

            parallaxRadius = ((float(layer) / float(parallaxLayers)) * maxdispl) + radius;
            // std::cout<<parallaxRadius<<std::endl;

            hit = hasIntersectedSphere(r, tHit, isect, testAlphaTexture, parallaxRadius);
            if(!hit) return false;
            pos2f = isect->uv;
             
            pos = int(float(resolution.y) * float(resolution.y) * pos2f.y) + int(float(resolution.x) * pos2f.x);
            //std::cout<<pos2f<<"||||"<<pos<<std::endl;
            disp = texels[pos][0];

            // std::cout<<(float(layer) / float(parallaxLayers))<<" |||| "<<disp<<std::endl<<std::endl<<std::endl<<std::endl;

            // if(hit && disp < (float(layer) / float(parallaxLayers))) return true;
            if(disp > (float(layer) / float(parallaxLayers))) {
                
                // Modify normal   
                
//                normal = isect->n

                // Bilinear interpolation to find height at exact hit point

                //normal = isect->n;

                disp1 = texels[pos][0];
                disp2 = texels[(pos + 1) % totalRes][0];
                disp3 = texels[(pos + resolution.y) % totalRes][0];
                disp4 = texels[(pos + resolution.y + 1) % totalRes][0];

                x = pos2f.x * float(resolution.x);
                y = pos2f.x * float(resolution.x);
                du1 = x - int(x);
                dv1 = y - int(y);

                a = disp1 * (1- du1) + disp2 * (du1);
                b = disp3 * (1- du1) + disp4 * (du1);
                c = disp1 * (1- dv1) + disp3 * (dv1);
                d = disp2 * (1- dv1) + disp4 * (dv1);
                
                val = a * (1 - dv1) + b * dv1;

                Vector3f dpdu, dpdv;
                Normal3f dndu, dndv;

                dpdu = Cross(isect->dpdu, Vector3f(du1, 1, 1));
                dpdv = Cross(isect->dpdv, Vector3f(1, dv1, 1));


                dndu = Normal3f(Cross(Vector3f(dndu), Vector3f((val - a) / du1, 1, 1)));
                dndv = Normal3f(Cross(Vector3f(dndv), Vector3f(1, (val - c) / dv1, 1)));

/*
                *isect = (*ObjectToWorld)(SurfaceInteraction(isect->p, isect->pError, isect->uv,
                                            isect->wo, dpdu, dpdv, dndu, dndv,
                                            isect->time, this));
*/
                return hit;
            }
        }
        return false;    
    }


    return hasIntersectedSphere(r, tHit, isect, testAlphaTexture, radius);
//    return false;
}

// Shadow intersects
bool DispSphere::IntersectP(const Ray &r, bool testAlphaTexture) const {

    
    // std::cout<<"IntersectP"<<std::endl;

    ProfilePhase p(Prof::ShapeIntersectP);
    Float phi;
    Point3f pHit;
    // Transform _Ray_ to object space
    Vector3f oErr, dErr;
    Ray ray = (*WorldToObject)(r, &oErr, &dErr);

    // Compute quadratic sphere coefficients

    // Initialize _EFloat_ ray coordinate values
    EFloat ox(ray.o.x, oErr.x), oy(ray.o.y, oErr.y), oz(ray.o.z, oErr.z);
    EFloat dx(ray.d.x, dErr.x), dy(ray.d.y, dErr.y), dz(ray.d.z, dErr.z);
    EFloat a = dx * dx + dy * dy + dz * dz;
    EFloat b = 2 * (dx * ox + dy * oy + dz * oz);
    EFloat c = ox * ox + oy * oy + oz * oz - EFloat(radius) * EFloat(radius);

    // Solve quadratic equation for _t_ values
    EFloat t0, t1;
    if (!Quadratic(a, b, c, &t0, &t1)) return false;

    // Check quadric shape _t0_ and _t1_ for nearest intersection
    if (t0.UpperBound() > ray.tMax || t1.LowerBound() <= 0) return false;
    EFloat tShapeHit = t0;
    if (tShapeHit.LowerBound() <= 0) {
        tShapeHit = t1;
        if (tShapeHit.UpperBound() > ray.tMax) return false;
    }

    // Compute sphere hit position and $\phi$
    pHit = ray((Float)tShapeHit);

    // Refine sphere intersection point
    pHit *= radius / Distance(pHit, Point3f(0, 0, 0));
    if (pHit.x == 0 && pHit.y == 0) pHit.x = 1e-5f * radius;
    phi = std::atan2(pHit.y, pHit.x);
    if (phi < 0) phi += 2 * Pi;

    // Test sphere intersection against clipping parameters
    if ((zMin > -radius && pHit.z < zMin) || (zMax < radius && pHit.z > zMax) ||
        phi > phiMax) {
        if (tShapeHit == t1) return false;
        if (t1.UpperBound() > ray.tMax) return false;
        tShapeHit = t1;
        // Compute sphere hit position and $\phi$
        pHit = ray((Float)tShapeHit);

        // Refine sphere intersection point
        pHit *= radius / Distance(pHit, Point3f(0, 0, 0));
        if (pHit.x == 0 && pHit.y == 0) pHit.x = 1e-5f * radius;
        phi = std::atan2(pHit.y, pHit.x);
        if (phi < 0) phi += 2 * Pi;
        if ((zMin > -radius && pHit.z < zMin) ||
            (zMax < radius && pHit.z > zMax) || phi > phiMax)
            return false;
    }
    return true;
}

Float DispSphere::Area() const { return phiMax * radius * (zMax - zMin); }

Interaction DispSphere::Sample(const Point2f &u, Float *pdf) const {
    Point3f pObj = Point3f(0, 0, 0) + radius * UniformSampleSphere(u);
    Interaction it;
    it.n = Normalize((*ObjectToWorld)(Normal3f(pObj.x, pObj.y, pObj.z)));
    if (reverseOrientation) it.n *= -1;
    // Reproject _pObj_ to sphere surface and compute _pObjError_
    pObj *= radius / Distance(pObj, Point3f(0, 0, 0));
    Vector3f pObjError = gamma(5) * Abs((Vector3f)pObj);
    it.p = (*ObjectToWorld)(pObj, pObjError, &it.pError);
    *pdf = 1 / Area();
    return it;
}

Interaction DispSphere::Sample(const Interaction &ref, const Point2f &u,
                           Float *pdf) const {
    Point3f pCenter = (*ObjectToWorld)(Point3f(0, 0, 0));

    // Sample uniformly on sphere if $\pt{}$ is inside it
    Point3f pOrigin =
        OffsetRayOrigin(ref.p, ref.pError, ref.n, pCenter - ref.p);
    if (DistanceSquared(pOrigin, pCenter) <= radius * radius) {
        Interaction intr = Sample(u, pdf);
        Vector3f wi = intr.p - ref.p;
        if (wi.LengthSquared() == 0)
            *pdf = 0;
        else {
            // Convert from area measure returned by Sample() call above to
            // solid angle measure.
            wi = Normalize(wi);
            *pdf *= DistanceSquared(ref.p, intr.p) / AbsDot(intr.n, -wi);
        }
        if (std::isinf(*pdf)) *pdf = 0.f;
        return intr;
    }

    // Sample sphere uniformly inside subtended cone

    // Compute coordinate system for sphere sampling
    Float dc = Distance(ref.p, pCenter);
    Float invDc = 1 / dc;
    Vector3f wc = (pCenter - ref.p) * invDc;
    Vector3f wcX, wcY;
    CoordinateSystem(wc, &wcX, &wcY);

    // Compute $\theta$ and $\phi$ values for sample in cone
    Float sinThetaMax = radius * invDc;
    Float sinThetaMax2 = sinThetaMax * sinThetaMax;
    Float invSinThetaMax = 1 / sinThetaMax;
    Float cosThetaMax = std::sqrt(std::max((Float)0.f, 1 - sinThetaMax2));

    Float cosTheta  = (cosThetaMax - 1) * u[0] + 1;
    Float sinTheta2 = 1 - cosTheta * cosTheta;

    if (sinThetaMax2 < 0.00068523f /* sin^2(1.5 deg) */) {
        /* Fall back to a Taylor series expansion for small angles, where
           the standard approach suffers from severe cancellation errors */
        sinTheta2 = sinThetaMax2 * u[0];
        cosTheta = std::sqrt(1 - sinTheta2);
    }

    // Compute angle $\alpha$ from center of sphere to sampled point on surface
    Float cosAlpha = sinTheta2 * invSinThetaMax +
        cosTheta * std::sqrt(std::max((Float)0.f, 1.f - sinTheta2 * invSinThetaMax * invSinThetaMax));
    Float sinAlpha = std::sqrt(std::max((Float)0.f, 1.f - cosAlpha*cosAlpha));
    Float phi = u[1] * 2 * Pi;

    // Compute surface normal and sampled point on sphere
    Vector3f nWorld =
        SphericalDirection(sinAlpha, cosAlpha, phi, -wcX, -wcY, -wc);    

    Point3f pWorld = pCenter + radius * Point3f(nWorld.x, nWorld.y, nWorld.z);

    // Return _Interaction_ for sampled point on sphere
    Interaction it;
    it.p = pWorld;
    it.pError = gamma(5) * Abs((Vector3f)pWorld);
    it.n = Normal3f(nWorld);

    
    if (reverseOrientation) it.n *= -1;

    // Uniform cone PDF.
    *pdf = 1 / (2 * Pi * (1 - cosThetaMax));

    return it;
}

Float DispSphere::Pdf(const Interaction &ref, const Vector3f &wi) const {
    Point3f pCenter = (*ObjectToWorld)(Point3f(0, 0, 0));
    // Return uniform PDF if point is inside sphere
    Point3f pOrigin =
        OffsetRayOrigin(ref.p, ref.pError, ref.n, pCenter - ref.p);
    if (DistanceSquared(pOrigin, pCenter) <= radius * radius)
        return Shape::Pdf(ref, wi);

    // Compute general sphere PDF
    Float sinThetaMax2 = radius * radius / DistanceSquared(ref.p, pCenter);
    Float cosThetaMax = std::sqrt(std::max((Float)0, 1 - sinThetaMax2));
    return UniformConePdf(cosThetaMax);
}

Float DispSphere::SolidAngle(const Point3f &p, int nSamples) const {
    Point3f pCenter = (*ObjectToWorld)(Point3f(0, 0, 0));
    if (DistanceSquared(p, pCenter) <= radius * radius)
        return 4 * Pi;
    Float sinTheta2 = radius * radius / DistanceSquared(p, pCenter);
    Float cosTheta = std::sqrt(std::max((Float)0, 1 - sinTheta2));
    return (2 * Pi * (1 - cosTheta));
}

void DispSphere::loadDispMap(){


    texels = ReadImage(dmapLoc, &resolution);
    totalRes = resolution.x * resolution.y;
    // texels = ReadImage(dmapLoc, &resolution);
    if (!texels) {
        Warning("Creating a constant grey texture to replace \"%s\".",
                dmapLoc.c_str());
        resolution.x = resolution.y = 1;
        RGBSpectrum *rgb = new RGBSpectrum[1];
        *rgb = RGBSpectrum(0.5f);
        texels.reset(rgb);
    }
/*
    std::unique_ptr<TextureMapping2D> map;

    map.reset(new UVMapping2D);

    d = new ImageTexture<Float, Float>(std::move(map), dmapLoc, false, 8.f, ImageWrap::Repeat, 1.f, true);
*/
  

    // std::cout<<resolution<<std::endl;
    
    
}

void DispSphere::generateDispMap(){
    generateDispMap(256,256,50,25);
}
void DispSphere::generateDispMap(int x, int y, Float alpha, Float beta){
    // Get map dimensions
    
    std::cout<<"Generating Displacement Map"<<std::endl;


    resolution = Point2i(x, y);
    totalRes = resolution.x * resolution.y;
    

    // texels = new RGBSpectrum[x * y];

    // d(u,v) = (y/2)(1 + cos(a pi u) * sin(b pi v))
    // Texture<Float> tex = CreateImageFloatTexture()
    /*
    for (int v = 0; v < y; v++){
        for (int u = 0; u < y; u++){
            texels[v*y + u] = RGBSpectrum((maxdispl / 2)*(1 + (cos(alpha * Pi * u) * sin(beta * Pi * v))));
        }
    }
    */
}



bool DispSphere::hasIntersectedSphere(const Ray &r, Float *tHit, SurfaceInteraction *isect,
                       bool testAlphaTexture, Float rad) const{
    
    //std::cout<<"Intersect"<<std::endl;

    ProfilePhase p(Prof::ShapeIntersect);
    Float phi;
    Point3f pHit;
    // Transform _Ray_ to object space
    Vector3f oErr, dErr;
    Ray ray = (*WorldToObject)(r, &oErr, &dErr);

    // Compute quadratic sphere coefficients

    // Initialize _EFloat_ ray coordinate values
    EFloat ox(ray.o.x, oErr.x), oy(ray.o.y, oErr.y), oz(ray.o.z, oErr.z);
    EFloat dx(ray.d.x, dErr.x), dy(ray.d.y, dErr.y), dz(ray.d.z, dErr.z);
    EFloat a = dx * dx + dy * dy + dz * dz;
    EFloat b = 2 * (dx * ox + dy * oy + dz * oz);
    EFloat c = ox * ox + oy * oy + oz * oz - EFloat(rad) * EFloat(rad);

    // Solve quadratic equation for _t_ values
    EFloat t0, t1;
    if (!Quadratic(a, b, c, &t0, &t1)) return false;

    // Check quadric shape _t0_ and _t1_ for nearest intersection
    if (t0.UpperBound() > ray.tMax || t1.LowerBound() <= 0) return false;
    EFloat tShapeHit = t0;
    if (tShapeHit.LowerBound() <= 0) {
        tShapeHit = t1;
        if (tShapeHit.UpperBound() > ray.tMax) return false;
    }

    // Compute sphere hit position and $\phi$
    pHit = ray((Float)tShapeHit);

    // Refine sphere intersection point
    pHit *= rad / Distance(pHit, Point3f(0, 0, 0));
    if (pHit.x == 0 && pHit.y == 0) pHit.x = 1e-5f * rad;
    phi = std::atan2(pHit.y, pHit.x);
    if (phi < 0) phi += 2 * Pi;

    // Test sphere intersection against clipping parameters
    if ((zMin > -rad && pHit.z < zMin) || (zMax < rad && pHit.z > zMax) ||
        phi > phiMax) {
        if (tShapeHit == t1) return false;
        if (t1.UpperBound() > ray.tMax) return false;
        tShapeHit = t1;
        // Compute sphere hit position and $\phi$
        pHit = ray((Float)tShapeHit);

        // Refine sphere intersection point
        pHit *= rad / Distance(pHit, Point3f(0, 0, 0));
        if (pHit.x == 0 && pHit.y == 0) pHit.x = 1e-5f * rad;
        phi = std::atan2(pHit.y, pHit.x);
        if (phi < 0) phi += 2 * Pi;
        if ((zMin > -rad && pHit.z < zMin) ||
            (zMax < rad && pHit.z > zMax) || phi > phiMax)
            return false;
    }

    // Find parametric representation of sphere hit
    Float u = phi / phiMax;
    Float theta = std::acos(Clamp(pHit.z / rad, -1, 1));
    Float v = (theta - thetaMin) / (thetaMax - thetaMin);

    // Compute sphere $\dpdu$ and $\dpdv$
    Float zRadius = std::sqrt(pHit.x * pHit.x + pHit.y * pHit.y);
    Float invZRadius = 1 / zRadius;
    Float cosPhi = pHit.x * invZRadius;
    Float sinPhi = pHit.y * invZRadius;
    Vector3f dpdu(-phiMax * pHit.y, phiMax * pHit.x, 0);
    Vector3f dpdv =
        (thetaMax - thetaMin) *
        Vector3f(pHit.z * cosPhi, pHit.z * sinPhi, -rad * std::sin(theta));

    // Compute sphere $\dndu$ and $\dndv$
    Vector3f d2Pduu = -phiMax * phiMax * Vector3f(pHit.x, pHit.y, 0);
    Vector3f d2Pduv =
        (thetaMax - thetaMin) * pHit.z * phiMax * Vector3f(-sinPhi, cosPhi, 0.);
    Vector3f d2Pdvv = -(thetaMax - thetaMin) * (thetaMax - thetaMin) *
                      Vector3f(pHit.x, pHit.y, pHit.z);

    // Compute coefficients for fundamental forms
    Float E = Dot(dpdu, dpdu);
    Float F = Dot(dpdu, dpdv);
    Float G = Dot(dpdv, dpdv);
    Vector3f N = Normalize(Cross(dpdu, dpdv));
    Float e = Dot(N, d2Pduu);
    Float f = Dot(N, d2Pduv);
    Float g = Dot(N, d2Pdvv);

    // Compute $\dndu$ and $\dndv$ from fundamental form coefficients
    Float invEGF2 = 1 / (E * G - F * F);
    Normal3f dndu = Normal3f((f * F - e * G) * invEGF2 * dpdu +
                             (e * F - f * E) * invEGF2 * dpdv);
    Normal3f dndv = Normal3f((g * F - f * G) * invEGF2 * dpdu +
                             (f * F - g * E) * invEGF2 * dpdv);

    // Compute error bounds for sphere intersection
    Vector3f pError = gamma(5) * Abs((Vector3f)pHit);

    // Initialize _SurfaceInteraction_ from parametric information
    *isect = (*ObjectToWorld)(SurfaceInteraction(pHit, pError, Point2f(u, v),
                                                 -ray.d, dpdu, dpdv, dndu, dndv,
                                                 ray.time, this));

    // Update _tHit_ for quadric intersection
    *tHit = (Float)tShapeHit;
    return true;

}

std::shared_ptr<Shape> CreateDispSphereShape(const Transform *o2w,
                                         const Transform *w2o,
                                         bool reverseOrientation,
                                         const ParamSet &params) {
    Float radius = params.FindOneFloat("radius", 1.f);
    Float zmin = params.FindOneFloat("zmin", -radius);
    Float zmax = params.FindOneFloat("zmax", radius);
    Float phimax = params.FindOneFloat("phimax", 360.f);
    Float maxdispl = params.FindOneFloat("displ", 1.f);
    std::string dmapLoc = params.FindOneString("displacementmap", "");    
    int parallaxLayers = params.FindOneInt("layers", 11);
    
    std::cout<<dmapLoc<<std::endl;   


    if(maxdispl == 0){std::cout<<"No displacement"<<std::endl;}
    else if(maxdispl < 0){std::cout<<"Does not support negative displacement mapping"<<std::endl;}

    return std::make_shared<DispSphere>(o2w, w2o, reverseOrientation, radius, zmin,
                                    zmax, phimax, maxdispl, dmapLoc, parallaxLayers);
}

}  // namespace pbrt
