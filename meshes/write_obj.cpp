#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
    const std::string &filename,
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    const Eigen::MatrixXd &UV,
    const Eigen::MatrixXi &UF,
    const Eigen::MatrixXd &NV,
    const Eigen::MatrixXi &NF)
{
    assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
    std::ofstream file;
    file.open(filename);
    if (!file.is_open())
        return false;

    // geometric vertex
    for (int i = 0; i < V.rows(); i++)
    {
        file << "v " << V.row(i) << "\n";
    }

    // texture coordinate
    for (int j = 0; j < UV.rows(); j++)
    {
        file << "vt " << UV.row(j) << "\n";
    }

    // vertex normal
    for (int k = 0; k < NV.rows(); k++)
    {
        file << "vn " << NV.row(k) << "\n";
    }

    // polygonal face element
    for (int l = 0; l < F.rows(); l++)
    {
        file << "f ";
        for (int m = 0; m < F.cols(); m++)
        {
            file << F(l, m) << "/" << UF(l, m)
                 << "/" << NF(l, m) << " ";
        }
        file << "\n";
    }

    file.close();
    return true;
}
