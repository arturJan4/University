using System;
using System.Collections.Generic;
using System.Linq;

// program wspierający rozwiazywanie kostek Rubika
// kostki o różnych rozmiarach mają różną reprezentację oraz różne sposoby rozwiązywania
// zasady GRASP
// 1. Creator -> wydzielona klasa tworząca instancje kostek (łatwo rozszerzalna)
// 2. Information Expert -> klasy dla kostek realizują własne "eskperckie" algorytmy rozwiązywania
// 3. Polymorphism -> abstrakcyjna kostka
// 4. Low Coupling -> brak dużej liczby zależności, niski zasięg, duża reużywalność kodu

namespace Cubes
{
	public abstract class Cube
	{
		public abstract List<string> GetSolution();
		public abstract List<string> GetRepresentation();
	}

	public class Cube2x2 : Cube
	{
		private List<string> representation;
		public Cube2x2(List<string> scramble)
		{
			this.representation = scramble;
		}

		public override List<string> GetSolution()
		{
			// placeholder
			return "L2 B’ L B’".Split(' ').ToList();
		}

		public override List<string> GetRepresentation()
		{
			return this.representation;
		}
	}

	public class Cube3x3 : Cube
	{
		private List<string> representation;
		public Cube3x3(List<string> scramble)
		{
			this.representation = scramble;
		}

		public override List<string> GetSolution()
		{
			// placeholder
			return "L2 B2 R2 B2 U2 F U2 L2 D2 B' R2 F2 L' F2 D' L' D2 L D' L U2".Split(' ').ToList();
		}

		public override List<string> GetRepresentation()
		{
			return this.representation;
		}
	}

	public class Cube4x4 : Cube
	{
		private List<string> representation;
		public Cube4x4(List<string> scramble)
		{
			this.representation = scramble;
		}

		public override List<string> GetSolution()
		{
			// placeholder
			return "B D22 F2' U F2 D2 U2 R L D' R2' F2' R2 F2 U2 D' L2 B L D' B2 R2 L2 B2 D2 U2' B R22 U22 D2 R D' U22 B2 F2 D2 U' R2 F2' D".Split(' ').ToList();
		}

		public override List<string> GetRepresentation()
		{
			return this.representation;
		}
	}

	class CubeBuilder
	{
		public Cube BuildCube(int n)
		{
			if (n == 2)
			{
				List<string> scramble = "F' R' U' F' U2 R2 F2 U2 R".Split(' ').ToList();
				return new Cube2x2(scramble);
			}

			if (n == 3)
			{
				List<string> scramble = "U2 B2 U' D' B L' D B U D B' L' B L' B2 U R F2 D R D U F U' R' ".Split(' ').ToList();
				return new Cube3x3(scramble);
			}

			if (n == 4)
			{
				List<string> scramble = "R2 F2 U' L2' F2 B U2 D22 F2 D2 L2 U2 F2 L2 U' L22 U' F' R2 L22 U2 R2' B2 D22 B2 F22 L2 D2 B22 R22 B2 R2 L22 F2' R' F2 R22 U R22 U2".Split(' ').ToList();
				return new Cube4x4(scramble);
			}

			return null;
		}
	}
}

public class Loop
{
	public static void Main(string[] args)
	{
		Cubes.CubeBuilder creator = new Cubes.CubeBuilder();
		int n = 2;
		Cubes.Cube cube = creator.BuildCube(n);
		Console.WriteLine(String.Join(" ", cube.GetRepresentation()));
	}
}