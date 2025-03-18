//
// Created by Zhen Chen on 2025/2/27.
//
#pragma once

#ifndef PROBABILITYMASSFUNCTIONS_H
#define PROBABILITYMASSFUNCTIONS_H

#include <span>
#include <vector>

class PMF {
    double truncatedQuantile;
    double stepSize;
    std::string distributionName;

public:
    PMF(double truncatedQuantile, double stepSize, std::string distributionName);

    // std::string getName();

    void checkName() const;

    static double poissonPMF(int k, double lambda);

    [[nodiscard]] std::vector<std::vector<std::vector<double> > > getPMF(std::span<double> demands) const;

    [[nodiscard]] std::vector<std::vector<std::vector<double> > >
    getPMFPoisson(std::span<double> demands) const;

    static int poissonQuantile(double p, double lambda);

    static double poissonCDF(int k, double lambda);
};

#endif // PROBABILITYMASSFUNCTIONS_H
