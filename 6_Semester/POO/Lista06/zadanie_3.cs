using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POO_Lista6
{
    public abstract class Tree
    {
    }
    public class TreeNode : Tree
    {
        public Tree Left { get; set; }
        public Tree Right { get; set; }
    }
    public class TreeLeaf : Tree
    {
        public int Value { get; set; }
    }

    public abstract class TreeVisitor
    {
        // return value here
        public int Visit(Tree tree)
        {
            if (tree is TreeNode)
                return this.VisitNode((TreeNode)tree);
            if (tree is TreeLeaf)
                return this.VisitLeaf((TreeLeaf)tree);

            throw new ArgumentException("wrong object type in tree");
        }
        public virtual int VisitNode(TreeNode node)
        {
            // tu wiedza o odwiedzaniu struktury
            if (node != null)
            {
                this.Visit(node.Left);
                this.Visit(node.Right);
            }
            return 0;
        }
        public virtual int VisitLeaf(TreeLeaf leaf)
        {
            return 0;
        }

    }

    public class HeightTreeVisitor : TreeVisitor
    {
        public override int VisitNode(TreeNode node)
        {
            int left = this.Visit(node.Left);
            int right = this.Visit(node.Right);

            if (left >= right)
            {
                return (left + 1);
            }

            return right + 1;
        }
        public override int VisitLeaf(TreeLeaf leaf)
        {
            return 0;
        }
    }

    class Program
    {
        static void Main()
        {
            // height 2
            Tree root = new TreeNode()
            {
                Left = new TreeNode()
                {
                    Left = new TreeLeaf() { Value = 1 },
                    Right = new TreeLeaf() { Value = 2 },
                },
                Right = new TreeLeaf() { Value = 3 }
            };

            TreeVisitor visitor = new HeightTreeVisitor();
            var height = visitor.Visit(root);

            Console.WriteLine("Height: {0}", height);

            // height 3
            Tree root2 = new TreeNode()
            {
                Left = root,
                Right = root
            };

            height = visitor.Visit(root2);

            Console.WriteLine("Height: {0}", height);

            // height 4
            Tree root3 = new TreeNode()
            {
                Left = root2,
                Right = new TreeLeaf() { Value = 1337 }
            };

            height = visitor.Visit(root3);

            Console.WriteLine("Height: {0}", height);

            Console.ReadLine();
        }
    }
}
