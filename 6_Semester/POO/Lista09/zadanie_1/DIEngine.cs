using System;
using System.Collections.Generic;

/// <summary>
/// Dependency Injection Engine demo.
/// </summary>
namespace DIEngine
{
    public class TypeResolutionException : Exception
    {
        public TypeResolutionException()
        {
        }
        public TypeResolutionException(string message)
            : base(message)
        {
        }
        public TypeResolutionException(string message, Exception inner)
            : base(message, inner)
        {
        }
    }

    public abstract class ObjectCreator
    {
        private Type type;
        public Type Type    // the Name property
        {
            get => type;
            set => type = value;
        }
        protected object instance = null;
        public ObjectCreator(Type type)
        {
            this.type = type;
        }
        public abstract object InstantiateObject();
    }

    public class ObjectCreatorSingleton : ObjectCreator
    {

        public ObjectCreatorSingleton(Type type) : base(type)
        {
        }

        private static readonly object _lock = new object();

        public override object InstantiateObject()
        {
            if (instance == null)
            {
                lock (_lock)
                {
                    // double checking after acquiring lock
                    if (instance == null)
                    {
                        instance = Activator.CreateInstance(this.Type);
                    }
                }
            }
            return instance;
        }
    }

    public class ObjectCreatorSimple : ObjectCreator
    {

        public ObjectCreatorSimple(Type type) : base(type)
        {
        }

        public override object InstantiateObject()
        {
            instance = Activator.CreateInstance(this.Type);
            return instance;
        }
    }


    public class SimpleContainer
    {
        // bind Type to class instantiating objects
        private readonly Dictionary<Type, ObjectCreator> typeDict;
        public SimpleContainer()
        {
            typeDict = new Dictionary<Type, ObjectCreator>();
        }

        public void RegisterType<T>(bool Singleton) where T : class
        {
            if (Singleton)
            {
                typeDict[typeof(T)] = new ObjectCreatorSingleton(typeof(T));
            }
            else
            {
                typeDict[typeof(T)] = new ObjectCreatorSimple(typeof(T));
            }
        }
        public void RegisterType<From, To>(bool Singleton) where To : From
        {
            if (Singleton)
            {
                typeDict[typeof(From)] = new ObjectCreatorSingleton(typeof(To));
            }
            else
            {
                typeDict[typeof(From)] = new ObjectCreatorSimple(typeof(To));
            }
        }

        public T Resolve<T>() where T : class
        {
            Type t = typeof(T);
            if (typeDict.ContainsKey(t))
                return (T)typeDict[t].InstantiateObject();

            if (t.IsAbstract)
                throw new TypeResolutionException("Can't resolve abstract class. Register related type.");

            if (t.IsInterface)
                throw new TypeResolutionException("Can't resolve interface. Register related type.");

            // T is not yet registered -> register as simple object and resolve
            this.RegisterType<T>(false);
            return (T)this.Resolve<T>();
        }
    }

    public class Program
    {
        public static void Main()
        {
            Console.WriteLine("Engine test");
            Console.ReadLine();
        }
    }
}