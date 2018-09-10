using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestConstructor
{
    class Base
    {
        public Base(int i)
        {
            Console.WriteLine("Base i constructor called");
        }

        public virtual void Foo()
        {
            Console.WriteLine("Base Foo");
        }
    }
}
