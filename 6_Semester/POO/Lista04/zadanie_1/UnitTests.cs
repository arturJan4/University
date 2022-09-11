using Microsoft.VisualStudio.TestTools.UnitTesting;
using Singleton;
using System.Threading;

namespace SingletonTests
{
    [TestClass]
    public class UnitTestSingletonGlobal
    {
        [TestMethod]
        public void TestNotNull()
        {
            var sin1 = SingletonGlobal.Instance();
            Assert.IsNotNull(sin1);
        }
        [TestMethod]
        public void TestSame()
        {
            var sin1 = SingletonGlobal.Instance();
            var sin2 = SingletonGlobal.Instance();

            Assert.AreSame(sin1, sin2);
            Assert.IsNotNull(sin1);
            Assert.IsNotNull(sin2);
        }
    }

    [TestClass]
    public class UnitTestSingletonThread
    {
        [TestMethod]
        public void TestNotNull()
        {
            var sin1 = SingletonThread.Instance();
            Assert.IsNotNull(sin1);
        }
        [TestMethod]
        public void TestSame()
        {
            SingletonThread sin1 = null;
            SingletonThread sin2 = null;

            Thread t1, t2;

            t1 = new Thread(() => sin1 = Singleton.SingletonThread.Instance());
            t2 = new Thread(() => sin2 = Singleton.SingletonThread.Instance());

            t1.Start();
            t2.Start();

            Assert.AreNotSame(sin1, sin2);

            t1.Join();
            t2.Join();

            Assert.AreNotSame(sin1, sin2);
            Assert.IsNotNull(sin1);
            Assert.IsNotNull(sin2);
        }
    }

    [TestClass]
    public class UnitTestSingletonTimed
    {
        [TestMethod]
        public void TestNotNull()
        {
            var sin1 = SingletonTimed.Instance();
            Assert.IsNotNull(sin1);
        }
        [TestMethod]
        public void TestSame()
        {
            var sin1 = SingletonTimed.Instance();
            var sin2 = SingletonTimed.Instance();

           // Assert.AreSame(sin1, sin2);
            
            Thread.Sleep(6000);
            var sin3 = SingletonTimed.Instance();
            
            Assert.AreSame(sin1, sin2);
            Assert.AreNotSame(sin1, sin3);
            Assert.IsNotNull(sin1);
            Assert.IsNotNull(sin2);
            Assert.IsNotNull(sin3);
        }
    }
}
