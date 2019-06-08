using System;
using System.Text.RegularExpressions;

namespace Lab7
{
    public sealed class Rational : IComparable<Rational>, IEquatable<Rational>
    {

        public Rational(long numerator, long denominator)
        {
            if (denominator == 0)
                throw new DivideByZeroException();
            
            _numerator = numerator;
            _denominator = denominator;

            if (_denominator < 0)
            {
                _denominator *= -1;
                _numerator *= -1;
            }
            
            Shrink();
        }

        public static Rational Parse(string x)
        {
            var regex = new Regex(@"^([-]?\b(0|[1-9][0-9]*))[|/%]([-]?[1-9][0-9]*)$");
            var match = regex.Match(x);
            if (match.Success)
            {
                var n = int.Parse(match.Groups[1].Value);
                var d = int.Parse(match.Groups[3].Value);
                return new Rational(n, d);   
            }
            else
                throw new FormatException("Input Error!");
        }

        public static bool TryParse(out Rational r, string x)
        {
            try
            {
                r = Parse(x);
                return true;
            }
            catch (FormatException)
            {
                r = null;
                return false;
            }
        }
        
        private static long GreatestCommonDivisor(long a, long b) => b == 0 ? a : GreatestCommonDivisor(b, a % b);
        
        private void Shrink()
        {
            var gcd = GreatestCommonDivisor(_numerator, _denominator);
            _numerator /= gcd;
            _denominator /= gcd;
        }
        
        private long _numerator;

        public long Numerator
        {
            get => _numerator;
            set
            {
                _numerator = value;
                Shrink();
            }
        }
        
        private long _denominator;
        public long Denominator
        {
            get => _denominator;
            set
            {
                _denominator = value;
                if (_denominator < 0)
                {
                    _denominator *= -1;
                    _numerator *= -1;
                }
                Shrink();
            }
        }

        ///////////////////////////////////////////interfaces///////////////////////////////////////////////////////////
        
        public override bool Equals(object obj) => obj is Rational && Equals((Rational) obj);

        public override int GetHashCode()
        {
            return (_numerator.GetHashCode() * 397) ^ _denominator.GetHashCode();
        }

        public int CompareTo(Rational obj) => (this - obj)._numerator.CompareTo(0);

        public bool Equals(Rational obj) => (this - obj)._denominator.Equals(0);

        public override string ToString() => _denominator ==  1 ? $"{_numerator}" : $"{_numerator}/{_denominator}";
        
        ///////////////////////////////////////////////casts////////////////////////////////////////////////////////////
        
        public static implicit operator Rational(long a) => new Rational(a, 1);
        
        public static implicit operator Rational(double a) => new Rational((long)(a * 1e9), (long)1e9);

        public static explicit operator Rational(Tuple<int, int> a) => new Rational(a.Item1, a.Item2);
        
        public static explicit operator Rational(Tuple<long, long> a) => new Rational(a.Item1, a.Item2);
                
        public static explicit operator double(Rational a) => a._numerator / (double) a._denominator;
        
        public static explicit operator Tuple<long, long>(Rational a) => new Tuple<long, long>(a._numerator, a._denominator);
        
        ////////////////////////////////////equality operators//////////////////////////////////////////////////////////

        public static bool operator ==(Rational a, Rational b) => object.ReferenceEquals(a, null) && a.Equals(b);
        
        public static bool operator !=(Rational a, Rational b) => !(a == b);

        public static bool operator >(Rational a, Rational b) => a.CompareTo(b) > 0;
        
        public static bool operator <(Rational a, Rational b) => a.CompareTo(b) < 0;

        public static bool operator >=(Rational a, Rational b) => a.CompareTo(b) >= 0;

        public static bool operator <=(Rational a, Rational b) => a.CompareTo(b) <= 0;
        
        ////////////////////////////////////math operators//////////////////////////////////////////////////////////////

        public static Rational operator +(Rational a, Rational b) => new Rational(a._numerator * b._denominator + 
                                                                                  b._numerator * a._denominator,
                                                                                  a._denominator * b._denominator);

        public static Rational operator *(Rational a, Rational b) => new Rational(a._numerator * b._numerator,
                                                                                  a._denominator * b._denominator);
        
        public static Rational operator -(Rational a) => -1 * a;

        public static Rational operator -(Rational a, Rational b) => a + -b;

        public static Rational operator /(Rational a, Rational b) => new Rational(a._numerator * b._denominator,
                                                                                  a._denominator * b._numerator);

        public static Rational operator ++(Rational a) => a + 1;

        public static Rational operator --(Rational a) => a - 1;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

    }
}