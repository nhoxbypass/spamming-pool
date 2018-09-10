using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestConstructor
{
    class Program
    {
        static void Main(string[] args)
        {
            Base c = new Child(1);

            c.Foo();

            Console.ReadLine();
        }
    }
}
