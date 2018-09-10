using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestConstructor
{
    class Child : Base
    {
        public Child() : base(1)
        {
            Console.WriteLine("Child constructor called");
        }

        public Child(int i) : base(i)
        {
            Console.WriteLine("Child i constructor called");
        }

        public void Foo()
        {
            //base.Foo();
            Console.WriteLine("Foo");
        }
    }
}


