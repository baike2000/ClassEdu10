﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace smaples29
{
    class Foo
    {
        public Foo()
        {
            Quux();
        }
        public virtual void Quux()
        {
            Console.WriteLine("Foo.Quux()");
        }
    }
    class Bar : Foo
    {
        protected string name;
        public Bar()
        {
            name = "Bar";
        }
        public override void Quux()
        {
            Console.WriteLine("Bar.Quux(),  " + name);
        }
        public void Quux(params object[] args)
        {
            Console.WriteLine("Bar.Quux(params object[])");
        }
    }
    class Baz : Bar
    {
        public Baz()
        {
            name = "Baz";
            Quux();
            ((Foo)this).Quux();
        }
    }
    void Main()
    {
        new Baz();
    }
​
​
}
