using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Factory
{
    public interface IShape
    {
        double Area();
    }

    public class Square : IShape
    {
        public double Length { get; set; }
        public double Area()
        {
            return Length * Length;
        }
    }

    public class Circle : IShape
    {
        public double Radius { get; set; }
        public double Area()
        {
            return Math.PI * Radius * Radius;
        }
    }

    public interface IShapeFactoryWorker
    {
        string ShapeName { get; }
        bool AcceptsParameters(string name, object[] parameters);
        IShape CreateObj(object[] parameters);
    }

    public class SquareFactoryWorker : IShapeFactoryWorker
    {
        public string ShapeName { get; } = "Square";

        public bool AcceptsParameters(string name, object[] parameters)
        {
            return name.Equals("Square") && parameters.Length == 1 && parameters[0] is double;
        }

        public IShape CreateObj(object[] parameters)
        {
            return new Square { Length = (double)parameters[0] };
        }
    }

    public class CircleFactoryWorker : IShapeFactoryWorker
    {
        public string ShapeName { get; } = "Circle";

        public bool AcceptsParameters(string name, object[] parameters)
        {
            return name.Equals("Circle") && parameters.Length == 1 && parameters[0] is double;
        }

        public IShape CreateObj(object[] parameters)
        {
            return new Circle { Radius = (double)parameters[0] };
        }
    }

    public class ShapeFactory
    {
        readonly Dictionary<string, IShapeFactoryWorker> _workers = new Dictionary<string, IShapeFactoryWorker>();
        public ShapeFactory()
        {
            _workers["Square"] = new SquareFactoryWorker();
        }

        public void RegisterWorker(IShapeFactoryWorker worker)
        {
            _workers[worker.ShapeName] = worker;
        }

        public IShape CreateShape(string ShapeName, params object[] parameters)
        {
            if (_workers.ContainsKey(ShapeName))
            {
                if (_workers[ShapeName].AcceptsParameters(ShapeName, parameters))
                    return _workers[ShapeName].CreateObj(parameters);
                else
                    throw new ArgumentException(String.Format("Invalid parameters."));
            }

            return null;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}
