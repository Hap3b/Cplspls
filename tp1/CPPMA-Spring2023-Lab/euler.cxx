/// Code élémentaire pour resoudre une équation différentielle avec
/// la méthode d'Euler implicite

#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;


/// @brief Fonction phi dans l'équation u'(x) = phi(x, u(x))
/// @param[in] x point où la fonction est évalué
/// @param[in] u prochain point calculé avec le schéma d'Euler
/// @return phi(x, u(x))
double phi(double x, double u){
    return 2*x*u;
}

/// @brief Fonction phi dans l'équation u'(x) = phi(x, u(x))
/// @param[in] x point où la fonction est évalué
/// @param[in] u prochain point calculé avec le schéma d'Euler
/// @return phi(x, u(x))
double phi2(double x, double u){
    return 50*x*cos(x);
}

/// @brief Calcule la solution de l'équation u'=phi(x, u(x))
///        selon Euler explicite avec n points et le vecteur
///        d'initialisation u0 sur l'intervalle [a, b]
/// @param[in] n période ou encore le nombre de points dans le 
///            schéma d'Euler explicite.
/// @param[in] u0 point initialisant le schéma d'Euler explicite
/// @param[in] a point ouvrant l'intervalle d'étude
/// @param[in] b point fermant l'intervalle d'étude
/// @param[in] phi fonction qui exprime u' en fonction de x et u
/// @return la liste de la solution en tout point
double* euler_explicite(unsigned int n, double u0, double a, double b, 
                        double (*phi_func)(double, double))
{
    double bcl  = u0;
    double h    = (b-a)/ static_cast<double>(n);
    double *sol = (double*)malloc((n+1)* sizeof(double));
    for (unsigned int i = 0; i < n; i++)
    {
        *sol     = bcl;
        double x = a+h*i; 
        bcl      = h*phi_func(x, bcl) + bcl;
        sol ++;
    }
    *sol = bcl;
    sol -= n;
    return sol;
}

/// @brief Calcule la solution de l'équation u'=phi(x, u(x))
///        selon Euler implicite avec n points et le vecteur
///        d'initialisation u0 sur l'intervalle [a, b]
/// @param[in] n période ou encore le nombre de points dans le 
///            schéma d'Euler implicite.
/// @param[in] u0 point initialisant le schéma d'Euler implicite
/// @param[in] a point ouvrant l'intervalle d'étude
/// @param[in] b point fermant l'intervalle d'étude
/// @param[in] phi fonction qui exprime u' en fonction de x et u
/// @return la liste de la solution en tout point
double newtonRaphson(double x_next, double u_current, double h, double (*phi_func)(double, double), double tolerance, int max_iter) {
    double u_next = u_current;
    for (int i = 0; i < max_iter; ++i) {
        double f_val = u_next - u_current - h * phi_func(x_next, u_next);
        double f_prime_val = 1 - h * (-1);
        
        double u_next_new = u_next - f_val / f_prime_val;

        if (std::abs(u_next_new - u_next) < tolerance) {
            return u_next_new;
        }
        u_next = u_next_new;
    }
    std::cerr << "Warning: Newton-Raphson did not converge" << std::endl;
    return u_next;
}

/// @brief Calcule la solution de l'équation u'=phi(x, u(x))
///        selon Euler implicite avec n points et le vecteur
///        d'initialisation u0 sur l'intervalle [a, b]
/// @param[in] n période ou encore le nombre de points dans le 
///            schéma d'Euler implicite.
/// @param[in] u0 point initialisant le schéma d'Euler implicite
/// @param[in] a point ouvrant l'intervalle d'étude
/// @param[in] b point fermant l'intervalle d'étude
/// @param[in] phi fonction qui exprime u' en fonction de x et u
/// @return la liste de la solution en tout point
double* euler_implicite(unsigned int n, double u0, double a, double b, 
                        double (*phi_func)(double, double))
{
    double bcl  = u0;
    double h    = (b-a)/ (double)(n);
    double *sol = (double*)malloc((n+1)* sizeof(double));
    for (unsigned int i = 0; i < n; i++)
    {
        *sol          = bcl;
        double x      = a+h*i; 
        double x_next = x+h;
        bcl           = newtonRaphson(x_next, bcl, h, phi_func, 1e-6, 100);
        sol ++;
    }
    *sol = bcl;
    sol -= n;
    return sol;
}

/// @brief main execution of euler solution
int main(){
    double u0      = 1;
    double a       = 0;
    double b       = 1;
    unsigned int n = 100;
    double *sol_exp    = euler_explicite(n, u0, a, b, phi);
    cout << "Solution of u' = 2xu between 0 and 1 initiates with 1 (Euler explicit):" << endl;
    for (unsigned int i = 0; i <= n; i++)
    {
        cout << *sol_exp << " ";
        sol_exp ++;
    } 
    cout << endl;

    double *sol_imp = euler_implicite(n, u0, a, b, phi);
    cout << "Solution of u' = 2xu between 0 and 1 initiates with 1 (Euler implicit):" << endl;
    for (unsigned int i = 0; i <= n; i++)
    {
        cout << *sol_imp << " ";
        sol_imp ++;
    } 
    cout << endl;

    double u02      = 0;
    double a2       = 0;
    double b2       = 2;
    unsigned int n2 = 100;
    double *sol2_ex = euler_explicite(n2, u02, a2, b2, phi2);
    cout << "Solution of u' = 50cos(x)u between 0 and 1 initiates with 1 (Euler explicit):" << endl;
    for (unsigned int i = 0; i <= n; i++)
    {
        cout << *sol2_ex << " ";
        sol2_ex ++;
    }
    cout << endl;
    double *sol_im2 = euler_implicite(n2, u02, a2, b2, phi2);
    cout << "Solution of u' = 50cos(x)u between 0 and 1 initiates with 1 (Euler implicit):" << endl;
    for (unsigned int i = 0; i <= n; i++)
    {
        cout << *sol_im2 << " ";
        sol_im2 ++;
    } 
    cout << endl;
    return 0;
}
