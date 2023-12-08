#include "euler_angles_to_transform.h"
#include <Eigen/Geometry>

Eigen::Affine3d euler_angles_to_transform(const Eigen::Vector3d &xzx)
{
    const double toRadians = M_PI / 180.0;
    double angleX1 = xzx(0) * toRadians;
    double angleZ = xzx(1) * toRadians;
    double angleX2 = xzx(2) * toRadians;

    Eigen::AngleAxisd rotationX1(angleX1, Eigen::Vector3d::UnitX());
    Eigen::AngleAxisd rotationZ(angleZ, Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd rotationX2(angleX2, Eigen::Vector3d::UnitX());

    Eigen::Affine3d transform = (Eigen::Affine3d)rotationX2 * rotationZ * rotationX1;

    return transform;
}
