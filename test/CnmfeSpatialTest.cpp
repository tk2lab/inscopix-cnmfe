#include "isxCnmfeSpatial.h"
#include "isxTest.h"
#include "catch.hpp"

#include <thread>

TEST_CASE("CircularConstraint", "[cnmfe-spatial]")
{
    SECTION("No padding")
    {
        isx::MatrixFloat_t input = {
            {0.02666485f, 0.64960629f, 0.0f, 0.99353473f, 0.32900842f},
            {0.02205889f, 0.39962318f, 0.0f, 0.00638578f, 0.71853864f},
            {0.5453062f, 0.0f, 0.0f, 0.72003801f, 0.7364942f },
            {0.02205889f, 0.0f, 0.85302743f, 0.00638578f, 0.71853864f},
            {0.0f, 0.0f, 0.73054572f, 0.72003801f, 0.7364942f },
            {0.02205889f, 0.39962318f, 0.85302743f, 0.00638578f, 0.71853864f},
            {0.5453062f, 0.76232453f, 0.73054572f, 0.72003801f, 0.7364942f }
        };

        const isx::MatrixFloat_t expResult = {
            {0.0f, 0.0f, 0.0f, 0.99353473f, 0.32900842f},
            {0.0f, 0.0f, 0.0f, 0.00638578f, 0.71853864f},
            {0.0f, 0.0f, 0.0f, 0.72003801f, 0.7364942f },
            {0.0f, 0.0f, 0.85302743f, 0.00638578f, 0.71853864f},
            {0.0f, 0.0f, 0.73054572f, 0.72003801f, 0.7364942f },
            {0.0f, 0.39962318f, 0.85302743f, 0.00638578f, 0.71853864f},
            {0.5453062f, 0.76232453f, 0.73054572f, 0.72003801f, 0.7364942f }
        };

        isx::circularConstraint(input);
        REQUIRE(arma::approx_equal(expResult, input, "reldiff", 1e-5f));
    }

    SECTION("With padding")
    {
        isx::MatrixFloat_t input = {
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.02666485f, 0.64960629f, 0.0f, 0.99353473f, 0.0f},
            {0.02205889f, 0.39962318f, 0.0f, 0.00638578f, 0.0f},
            {0.5453062f, 0.0f, 0.0f, 0.72003801f, 0.0f},
            {0.02205889f, 0.0f, 0.85302743f, 0.00638578f, 0.0f},
            {0.0f, 0.0f, 0.73054572f, 0.72003801f, 0.0f},
            {0.02205889f, 0.39962318f, 0.0f, 0.0f, 0.0f},
            {0.5453062f, 0.76232453f, 0.0f, 0.72003801f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
        };

        const isx::MatrixFloat_t expResult = {
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.99353473f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.00638578f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.72003801f, 0.0f},
            {0.0f, 0.0f, 0.85302743f, 0.00638578f, 0.0f},
            {0.0f, 0.0f, 0.73054572f, 0.72003801f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
        };

        isx::circularConstraint(input);
        REQUIRE(arma::approx_equal(expResult, input, "reldiff", 1e-5f));
    }
}

TEST_CASE("ConnectivityConstraint", "[cnmfe-spatial]")
{
    SECTION("7x5 Image 3x3 Filter")
    {
        isx::MatrixFloat_t input = {
            {0.0f, 0.01960629f, 0.0f, 0.0f, 0.32900842f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.71853864f},
            {0.0f, 0.0f, 0.0f, 0.72003801f, 0.7364942f},
            {0.02205889f, 0.0f, 0.85302743f, 0.71853864f, 0.71853864f},
            {0.0f, 0.0f, 0.0f, 0.99003801f, 0.99003801f},
            {0.0f, 0.0102318f, 0.0f, 0.00638578f, 0.71853864f},
            {0.0f, 0.0f, 0.0f, 0.72003801f, 0.0364942f}
        };

        const isx::MatrixFloat_t expResult = {
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.72003801f, 0.7364942f},
            {0.0f, 0.0f, 0.0f, 0.71853864f, 0.71853864f},
            {0.0f, 0.0f, 0.0f, 0.99003801f, 0.99003801f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
        };

        isx::connectivityConstraint(input, 0.01f, 3);
        REQUIRE(arma::approx_equal(expResult, input, "reldiff", 1e-5f));
    }

    SECTION("10x7 Image 3x3 Filter")
    {
        isx::MatrixFloat_t input = {
            {0.0f, 0.0f, 0.01744436f, 0.0f, 0.97621071f, 0.0f, 0.9528444f},
            {0.62881434f, 0.83203345f, 0.50110303f, 0.16740358f, 0.0f, 0.63879898f, 0.96294037f},
            {0.0f, 0.8065605f, 0.25675229f, 0.9635909f, 0.0f, 0.30453204f, 0.58202867f},
            {0.48618324f, 0.0f, 0.77614119f, 0.88666595f, 0.58512138f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.6060305f, 0.87294948f, 0.0f, 0.97611164f, 0.0f},
            {0.0f, 0.98554714f, 0.63691596f, 0.36015368f, 0.0f, 0.64080124f, 0.30883799f},
            {0.95896007f, 0.0f, 0.12776285f, 0.0f, 0.0f, 0.60252794f, 0.0f},
            {0.98241664f, 0.69657024f, 0.0f, 0.922574f, 0.0f, 0.68952654f, 0.76259897f},
            {0.0f, 0.88932858f, 0.31473466f, 0.65902884f, 0.0f, 0.16937417f, 0.29382286f},
            {0.41813767f, 0.33648673f, 0.99479987f, 0.31366448f, 0.18349745f, 0.0520341f, 0.56919139f}
        };

        const isx::MatrixFloat_t expResult = {
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.88932858f, 0.31473466f, 0.65902884f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.33648673f, 0.99479987f, 0.31366448f, 0.0f, 0.0f, 0.0f}
        };

        isx::connectivityConstraint(input, 0.01f, 3);
        REQUIRE(arma::approx_equal(expResult, input, "reldiff", 1e-5f));
    }

    SECTION("10x8 Image 5x5 Filter")
    {
        isx::MatrixFloat_t input = {
            {0.0f, 0.15787503f, 0.0f, 0.29073065f, 0.81811875f, 0.0f, 0.0f, 0.275673f},
            {0.0f, 0.0f, 0.91952363f, 0.0f, 0.0f, 0.63051927f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.617933f, 0.0f, 0.92494512f, 0.0f, 0.0f, 0.03574913f},
            {0.0f, 0.3637079f, 0.0f, 0.04506048f, 0.11927078f, 0.78585828f, 0.21393045f, 0.0f},
            {0.84556873f, 0.0f, 0.38221045f, 0.27206654f, 0.0f, 0.0f, 0.70224899f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.60058221f, 0.94816475f, 0.0f, 0.0f, 0.88666049f},
            {0.51430828f, 0.0f, 0.16239755f, 0.61052232f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.77196889f, 0.81663841f, 0.26760101f, 0.25322105f, 0.80747093f, 0.32582035f},
            {0.2395411f, 0.0f, 0.0f, 0.0f, 0.54806709f, 0.54470913f, 0.23827518f, 0.74577937f},
            {0.58445572f, 0.0f, 0.0f, 0.0f, 0.86769724f, 0.33438723f, 0.47931346f, 0.46307469f}
        };

        const isx::MatrixFloat_t expResult = {
            {0.0f, 0.15787503f, 0.0f, 0.29073065f, 0.81811875f, 0.0f, 0.0f, 0.275673f},
            {0.0f, 0.0f, 0.91952363f, 0.0f, 0.0f, 0.63051927f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.617933f, 0.0f, 0.92494512f, 0.0f, 0.0f, 0.03574913f},
            {0.0f, 0.3637079f, 0.0f, 0.04506048f, 0.11927078f, 0.78585828f, 0.21393045f, 0.0f},
            {0.84556873f, 0.0f, 0.38221045f, 0.27206654f, 0.0f, 0.0f, 0.70224899f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.60058221f, 0.94816475f, 0.0f, 0.0f, 0.88666049f},
            {0.51430828f, 0.0f, 0.16239755f, 0.61052232f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.77196889f, 0.81663841f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.2395411f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.58445572f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
        };

        isx::connectivityConstraint(input, 0.01f, 5);
        REQUIRE(arma::approx_equal(expResult, input, "reldiff", 1e-5f));
    }
}

TEST_CASE("CnmfeSpatialRegressionParallel", "[cnmfe-spatial]")
{
    SECTION("single component per pixel")
    {
        const float inYdata[60] = {
            1.03741539f, 21.85586756f, 16.67763465f, 57.27598156f, 38.64771696f,
            80.373977f, 64.95404632f, 87.34008431f, 61.05377408f, 18.73586471f,
            64.71167135f, 16.95314142f, 50.18745921f, 41.85081805f, 87.85590855f,
            89.80071182f, 69.44386778f, 98.33592482f, 86.08319232f, 90.62772769f,
            49.62817177f, 68.76740932f, 63.80539847f, 79.4547887f, 49.57732931f,
            24.81011684f, 95.09640316f, 66.68989729f, 82.48704645f, 16.96362576f,
            97.08460121f, 75.82779868f, 47.79740135f, 70.35291738f, 46.16976625f,
            16.26060466f, 13.3829529f,  8.40596512f,  3.87483758f, 54.7837783f,
            46.56684754f, 52.10847115f, 18.55416869f, 34.69019538f, 43.55554648f,
            92.52000773f,  5.30594245f, 13.87386998f, 14.21110855f, 34.54986401f,
            69.91073914f, 70.24274241f, 94.05244095f, 94.5517417f, 24.31156753f,
            46.3534714f, 87.04082964f,  3.94548177f,  3.85709232f, 35.29169532f
        };
        const isx::CubeFloat_t inY(inYdata, 4, 3, 5);

        isx::MatrixFloat_t inC ={
            {3.57f, 0.89f, 1.03f, 9.4f, 1.2f},
            {5.6f, 3.1f, 12.1f, 8.4f, 7.0f}
        };
        isx::MatrixFloat_t inNoise ={
            {0.3f, 0.3f, 0.3f, 0.3f},
            {0.3f, 0.3f, 0.3f, 0.3f},
            {0.3f, 0.3f, 0.3f, 0.3f}
        };
        isx::ColumnFloat_t inCct = {0.9997f, 0.9995f};

        std::vector<arma::uvec> inIndC;
        inIndC.emplace_back(arma::uvec{});
        inIndC.emplace_back(arma::uvec{0});
        inIndC.emplace_back(arma::uvec{1});
        inIndC.emplace_back(arma::uvec{});
        inIndC.emplace_back(arma::uvec{0});

        const std::pair<size_t, size_t> inPixelRange(0,5);

        isx::MatrixFloat_t expectedA = {{0.0f,0.0f},{0.0f,0.0f},{0.0f,1.28880965f},{0.0f,0.0f},{0.0f,0.0f}};

        isx::MatrixFloat_t outA;
        isx::regressionParallel(inY, inC, inNoise, inIndC, inPixelRange, inCct, outA);

        REQUIRE(arma::approx_equal(expectedA, outA, "reldiff", 1e-5f));
    }
}
