#include "GaloisFieldPolynomial.h"

namespace galois
{

   GaloisFieldPolynomial::GaloisFieldPolynomial(GaloisField* _gf)
   {
      gf = _gf;
      poly.clear();
   }


   GaloisFieldPolynomial::GaloisFieldPolynomial(GaloisField* _gf, unsigned int size, GaloisFieldElement* gfe)
   {
      if (size > 0)
      {
         gf = _gf;
         poly.resize(size+1);

         if (gfe != NULL)
         {
            for(unsigned int i = 0; i <= size; i++)
            {
               poly[i] = gfe[i];
            }
         }
         else
         {
            for(unsigned int i = 0; i < poly.size(); i++)
            {
               poly[i] = GaloisFieldElement(gf,0);
            }
         }
      }
      else
      {
         gf = NULL;
         poly.clear();
      }
   }


   GaloisFieldPolynomial::GaloisFieldPolynomial(const GaloisFieldPolynomial& gfp)
   {
      gf   = gfp.gf;
      poly = gfp.poly;
   }


   GaloisFieldPolynomial::GaloisFieldPolynomial(const GaloisFieldElement& gfe)
   {
      gf = gfe.field();
      poly.clear();
      poly.push_back(gfe);
   }


   bool GaloisFieldPolynomial::valid() const
   {
      return (poly.size() > 0);
   }


   unsigned int GaloisFieldPolynomial::deg() const
   {
      return (poly.size()-1);
   }


   GaloisField* GaloisFieldPolynomial::field() const
   {
      return gf;
   }


   void GaloisFieldPolynomial::set_degree(const unsigned int& x)
   {
      poly.resize(x - 1,GaloisFieldElement(gf,0));
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator=(const GaloisFieldPolynomial& gfp)
   {
      if (this == &gfp)
        return *this;

      gf   = gfp.gf;
      poly = gfp.poly;

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator=(const GaloisFieldElement& gfe)
   {
      poly.clear();
      gf = gfe.field();
      poly.push_back(gfe);
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator+=(const GaloisFieldPolynomial& gfp)
   {
      if (gf == gfp.gf)
      {
         if (poly.size() < gfp.poly.size())
         {
            unsigned int j = 0;
            for (unsigned int i = 0; i < poly.size(); i++)
            {
               poly[i] += gfp.poly[j++];
            }

            for ( ; j < gfp.poly.size(); j++)
            {
               poly.push_back(gfp.poly[j]);
            }
         }
         else
         {
            unsigned int i = 0;
            for (unsigned int j = 0; j < gfp.poly.size(); j++)
            {
               poly[i++] += gfp.poly[j];
            }
         }


         simplify(*this);

      }

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator+=(const GaloisFieldElement& gfe)
   {
      poly[0] += gfe;
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator-=(const GaloisFieldPolynomial& gfe)
   {
      return (*this += gfe);
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator-=(const GaloisFieldElement& gfe)
   {
      poly[0] -= gfe;
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator*=(const GaloisFieldPolynomial& gfp)
   {
      if (gf == gfp.gf)
      {
         GaloisFieldPolynomial product(gf,deg() + gfp.deg() + 1);

         for (unsigned int  i= 0; i < poly.size(); i++)
         {
            for (unsigned int j = 0; j < gfp.poly.size(); j++)
            {
               product.poly[i + j] += poly[i] * gfp.poly[j];
            }
         }

         simplify(product);
         poly = product.poly;
      }
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator*=(const GaloisFieldElement& gfe)
   {
      if (gf == gfe.field())
      {
         for(unsigned int i = 0; i < poly.size(); i++)
         {
            poly[i] *= gfe;
         }
      }
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator/=(const GaloisFieldPolynomial& gfp)
   {
      if ((gf == gfp.gf) &&
          (deg() >= gfp.deg()) &&
          (gfp.deg() >= 0)
         )
      {

         GaloisFieldPolynomial quotent(gf, deg() - gfp.deg() + 1);
         GaloisFieldPolynomial remainder(gf, gfp.deg() - 1);

         for(int i = deg(); i >= 0; i--)
         {
            if (i <= (int)quotent.deg())
              quotent[i] = remainder[remainder.deg()] / gfp[gfp.deg()];

            for(int j = remainder.deg(); j > 0; j--)
            {
               remainder[j] = remainder[j - 1] + (quotent[i] * gfp[j]);
            }
            remainder[0] = poly[i] + (quotent[i] * gfp[0]);
         }

         simplify(quotent);

         poly = quotent.poly;
      }

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator/=(const GaloisFieldElement& gfe)
   {
      if (gf == gfe.field())
      {
         for (unsigned int i = 0;  i < poly.size(); i++)
         {
            poly[i] /= gfe;
         }
      }
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator%=(const GaloisFieldPolynomial& gfp)
   {

      if ((gf == gfp.gf) &&
          (deg() >= gfp.deg()) &&
          (gfp.deg() >= 0)
         )
      {

         GaloisFieldPolynomial quotent(gf, deg() - gfp.deg() + 1);
         GaloisFieldPolynomial remainder(gf, gfp.deg() - 1);

         for(int i = deg(); i >= 0; i--)
         {
            if (i <= (int)quotent.deg())
              quotent[i] = remainder[remainder.deg()] / gfp[gfp.deg()];

            for(int j = remainder.deg(); j > 0; j--)
            {
               remainder[j] = remainder[j - 1] + (quotent[i] * gfp[j]);
            }
            remainder[0] = poly[i] + (quotent[i] * gfp[0]);
         }

         simplify(remainder);
         poly = remainder.poly;
      }

      return *this;

   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator%=(const unsigned int& power)
   {
      if (poly.size() >= power)
        poly.resize(power);
      simplify(*this);
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator^=(const int& n)
   {
      GaloisFieldPolynomial result = *this;

      for (int i = 0; i < n; i++)
      {
         result *= *this;
      }

      *this = result;

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator<<=(const unsigned int& n)
   {
      if (poly.size() > 0)
      {
         int initial_size = poly.size();
         poly.resize(poly.size() + n, GaloisFieldElement(gf,0));

         for(int i = initial_size - 1; i >= 0; i--)
         {
            poly[i + n] = poly[i];
         }

         for(unsigned int i = 0; i < n; i++)
         {
            poly[i] = 0;
         }
      }

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator>>=(const unsigned int& n)
   {
      if (n  < deg()+1)
      {
         for(unsigned int i = 0;  i < (n + 1); i++)
         {
            poly[i] = poly[i + n];
         }

         poly.resize(poly.size() - n,GaloisFieldElement(gf,0));

      }

      return *this;
   }


   const GaloisFieldElement& GaloisFieldPolynomial::operator[](const unsigned int& term) const
   {
      if (term < poly.size())
        return poly[term];
      else
        return poly[0];
   }


   GaloisFieldElement& GaloisFieldPolynomial::operator[](const unsigned int& term)
   {
      if (term < poly.size())
        return poly[term];
      else
        return poly[0];
   }


   GaloisFieldElement GaloisFieldPolynomial::operator()(const GaloisFieldElement& value)
   {
      GaloisFieldElement result(gf,0);

      if (poly.size() > 0)
      {
        result = poly[poly.size() - 1];
        for(int i = poly.size() - 2; i >= 0; i--)
        {
           result = poly[i] + (result * value);
        }
      }
      return result;
   }


   GaloisFieldElement GaloisFieldPolynomial::operator()(GFSymbol value)
   {
      return (*this)(GaloisFieldElement(gf,value));
   }


   bool GaloisFieldPolynomial::operator==(const GaloisFieldPolynomial& gfp) const
   {
      if (gf == gfp.gf)
      {
         if (poly.size() != gfp.poly.size())
           return false;
         else
         {
            for (unsigned int i = 0; i < poly.size(); i++)
            {
               if (poly[i] != gfp.poly[i])
                 return false;
            }
            return true;
         }
      }
      else
        return false;
   }


   bool GaloisFieldPolynomial::operator!=(const GaloisFieldPolynomial& gfp) const
   {
      return !(*this == gfp);
   }


   GaloisFieldPolynomial GaloisFieldPolynomial::derivative()
   {
      if ((*this).poly.size() > 1)
      {
         GaloisFieldPolynomial deriv(gf,deg());
         for (unsigned int i = 0; i < poly.size() - 1; i++)
         {
            if ((i + 1) & 1 == 1)
              deriv.poly[i] = poly[i + 1];
            else
              deriv.poly[i] = 0;
            //poly[i] = (((i + 1) & 1 == 1) ? poly[i + 1] : GaloisFieldElement(gf,0));   // Note: something weird happens when you use this line.
         }
         simplify(deriv);
         return deriv;
     }
     return GaloisFieldPolynomial(gf,0);
   }


   void GaloisFieldPolynomial::simplify()
   {
      simplify(*this);
   }


   void GaloisFieldPolynomial::simplify(GaloisFieldPolynomial& gfp)
   {
      int last = gfp.poly.size() - 1;

      while((last >= 0) && (gfp.poly.size() > 0))
      {
         if (gfp.poly[last] == 0)
           gfp.poly.pop_back();
         else
           break;

         last = gfp.poly.size() - 1;
      }
   }


   GaloisFieldPolynomial operator+(const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result += b;
      return result;
   }


   GaloisFieldPolynomial operator + (const GaloisFieldPolynomial& a, const GaloisFieldElement& b)
   {
      GaloisFieldPolynomial result = a;
      result += b;
      return result;
   }


   GaloisFieldPolynomial operator + (const GaloisFieldElement& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = b;
      result += a;
      return result;
   }


   GaloisFieldPolynomial operator + (const GaloisFieldPolynomial& a, const GFSymbol& b)
   {
      return a + GaloisFieldElement(a.field(),b);
   }


   GaloisFieldPolynomial operator + (const GFSymbol& a, const GaloisFieldPolynomial& b)
   {
      return b + GaloisFieldElement(b.field(),a);
   }


   GaloisFieldPolynomial operator-(const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result -= b;
      return result;
   }

   GaloisFieldPolynomial operator - (const GaloisFieldPolynomial& a, const GaloisFieldElement& b)
   {
      GaloisFieldPolynomial result = a;
      result -= b;
      return result;
   }


   GaloisFieldPolynomial operator - (const GaloisFieldElement& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = b;
      result -= a;
      return result;
   }


   GaloisFieldPolynomial operator - (const GaloisFieldPolynomial& a, const GFSymbol& b)
   {
      return a - GaloisFieldElement(a.field(),b);
   }


   GaloisFieldPolynomial operator - (const GFSymbol& a, const GaloisFieldPolynomial& b)
   {
      return b - GaloisFieldElement(b.field(),a);
   }


   GaloisFieldPolynomial operator*(const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result *= b;
      return result;
   }


   GaloisFieldPolynomial operator*(const GaloisFieldElement& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = b;
      result *= a;
      return result;
   }


   GaloisFieldPolynomial operator*(const GaloisFieldPolynomial& a, const GaloisFieldElement& b)
   {
      GaloisFieldPolynomial result = a;
      result *= b;
      return result;
   }

   GaloisFieldPolynomial operator/(const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result /= b;
      return result;
   }


   GaloisFieldPolynomial operator/(const GaloisFieldPolynomial& a, const GaloisFieldElement& b)
   {
      GaloisFieldPolynomial result = a;
      result /= b;
      return result;
   }


   GaloisFieldPolynomial operator%(const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result %= b;
      return result;
   }

   GaloisFieldPolynomial operator%(const GaloisFieldPolynomial& a, const unsigned int& power)
   {
      GaloisFieldPolynomial result = a;
      result %= power;
      return result;
   }

   GaloisFieldPolynomial operator^(const GaloisFieldPolynomial& a, const int& n)
   {
      GaloisFieldPolynomial result = a;
      result ^= n;
      return result;
   }


   GaloisFieldPolynomial operator<<(const GaloisFieldPolynomial& a, const unsigned int& n)
   {
      GaloisFieldPolynomial result = a;
      result <<= n;
      return result;
   }


   GaloisFieldPolynomial operator>>(const GaloisFieldPolynomial& a, const unsigned int& n)
   {
      GaloisFieldPolynomial result = a;
      result >>= n;
      return result;
   }


   GaloisFieldPolynomial gcd(const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      if (a == b)
      {
         if (!a.valid() == 0)
           return b;

         if (!b.valid() == 0)
           return a;

         GaloisFieldPolynomial x = a % b;
         GaloisFieldPolynomial y = b;
         GaloisFieldPolynomial z = x;

         while ((z = y % x).valid())
         {
            y = x;
            x = z;
         }
         return x;
      }
      return GaloisFieldPolynomial();
   }


   std::ostream& operator << (std::ostream& os, const GaloisFieldPolynomial& gfp)
   {

      if (gfp.deg() >= 0)
      {
         for (unsigned int i = 0; i < gfp.poly.size(); i++)
         {
            os << gfp.poly[i].index()
               << ((i != (gfp.deg())) ? " " : "");
         }

         std::cout << "poly form: ";

         for (unsigned int i = 0; i < gfp.poly.size(); i++)
         {
            os //<< gfp.poly[i].poly()
               //<< ((i != (gfp.deg())) ? " " : "");
               << "x^"
               << i
               << ((i != (gfp.deg())) ? " + " : "");
         }
      }
      return os;
   }

}
