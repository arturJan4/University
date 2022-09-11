using System;

/*
Nie spełnia LSP, ponieważ prostokąt ma mocniejsze warunki wyjściowe niż kwadrat.
tj. zastąpienie klasy Rectangle klasą Square spowoduje, że możemy źle policzyć pole

rozwiązanie -> wporowadzenie abstrakcyjnej klasy Shape, która może być zastępowana przez Square, Rectangle (i inne przez rozszerzanie!)
*/
public abstract class Shape
{
	public abstract int GetArea();
}

public class Rectangle : Shape
{
	public int Width { get; set; }

	public int Height { get; set; }

	public override int GetArea()
	{
		return Width * Height;
	}
}

public class Square : Shape
{
	public int Length { get; set; }

	public override int GetArea()
	{
		return Length * Length;
	}
}

public class AreaCalculator
{
	public int CalculateArea(Shape s)
	{
		return s.GetArea();
	}
}

public class Test
{
	public static void Main(string[] args)
	{
		int w = 4, h = 5;
		Shape rect = new Rectangle()
		{Width = w, Height = h};
		AreaCalculator calc = new AreaCalculator();
		Console.WriteLine("prostokąt o wymiarach {0} na {1} ma pole {2}", w, h, calc.CalculateArea(rect));
	}
}