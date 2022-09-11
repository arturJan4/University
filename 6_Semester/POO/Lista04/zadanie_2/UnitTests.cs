using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Factory;

namespace FactoryTests
{
    [TestClass]
    public class UnitTests
    {
        [TestMethod]
        public void ClientTests()
        {
            ShapeFactory factory = new ShapeFactory();

            IShape square = factory.CreateShape("Square", 5.0);

            Assert.IsNotNull(square);
            Assert.AreEqual(square.Area(), (5 * 5), 0.001);
            Assert.AreNotEqual(square.Area(), (5 * 6), 0.001);
        }

        public void ExtensionTests()
        {
            ShapeFactory factory = new ShapeFactory();

            factory.RegisterWorker(new CircleFactoryWorker());
            IShape circle = factory.CreateShape("Circle", 5.0);

            Assert.IsNotNull(circle);
            Assert.AreEqual(circle.Area(), (5 * 5 * Math.PI), 0.001);
            Assert.AreNotEqual(circle.Area(), (5 * 6 * Math.PI), 0.001);
        }

    }
}
