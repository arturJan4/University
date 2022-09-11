using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POO_Lista6
{
    public class Context
    {
        // variable is represented as a string, and is either True or False
        private Dictionary<string, bool> vars;

        public Context()
        {
            vars = new Dictionary<string, bool>();
        }

        public bool GetValue(string VariableName)
        {
            if (vars.ContainsKey(VariableName))
                return vars[VariableName];

            throw new ArgumentException("Variable {0} not present in dict", VariableName);
        }

        public bool SetValue(string VariableName, bool Value)
        {
            vars.Add(VariableName, Value);
            return Value;
        }
    }
    public abstract class AbstractExpression
    {
        public abstract bool Interpret(Context context);
    }
    public class ConstExpression : AbstractExpression
    {
        private bool _val;

        public ConstExpression(bool value)
        {
            _val = value;
        }

        public override bool Interpret(Context context)
        {
            // regardless of context const always has the same boolean value
            return _val;
        }
    }

    public class VariableExpression : AbstractExpression
    {
        private string _token;

        public VariableExpression(string token)
        {
            _token = token;
        }

        public override bool Interpret(Context context)
        {
            // get variable value from current context
            return context.GetValue(_token);
        }
    }

    public abstract class BinaryExpression : AbstractExpression
    {
        // need 2 abstract expressions and specific binary function 
        protected AbstractExpression _ex1, _ex2;

        public BinaryExpression(AbstractExpression expression, AbstractExpression expression2)
        {
            _ex1 = expression;
            _ex2 = expression;
        }
    }
    public abstract class UnaryExpression : AbstractExpression
    {
        protected AbstractExpression _ex;

        public UnaryExpression(AbstractExpression expression)
        {
            _ex = expression;
        }
    }

    public class NotExpression : UnaryExpression
    {
        public NotExpression(AbstractExpression expression)
            : base(expression) { }

        public override bool Interpret(Context context)
        {
            return !(this._ex.Interpret(context));
        }
    }

    public class AndExpression : BinaryExpression
    {
        public AndExpression(AbstractExpression expression, AbstractExpression expression2)
            : base(expression, expression2) { }

        public override bool Interpret(Context context)
        {
            return (this._ex1.Interpret(context)) && (this._ex2.Interpret(context));
        }
    }

    public class OrExpression : BinaryExpression
    {
        public OrExpression(AbstractExpression expression, AbstractExpression expression2)
            : base(expression, expression2) { }

        public override bool Interpret(Context context)
        {
            return (this._ex1.Interpret(context)) || (this._ex2.Interpret(context));
        }
    }

    class Program
    {
        static void test_1()
        {
            // klient
            Context ctx = new Context();
            ctx.SetValue("x", false);
            ctx.SetValue("y", true);

            // true/false tokens
            var trueConst = new ConstExpression(true);
            var falseConst = new ConstExpression(false);

            AbstractExpression exp = trueConst;
            bool Value = exp.Interpret(ctx);
            Console.WriteLine(Value); // expected: True

            exp = falseConst;
            Value = exp.Interpret(ctx);
            Console.WriteLine(Value); // expected: False

            exp = new AndExpression(trueConst, trueConst);
            Value = exp.Interpret(ctx);
            Console.WriteLine(Value); // expected: True

            exp = new AndExpression(falseConst, trueConst);
            Value = exp.Interpret(ctx);
            Console.WriteLine(Value); // expected: False

            exp = new NotExpression(exp);
            Value = exp.Interpret(ctx);
            Console.WriteLine(Value); // expected: True

            exp = new AndExpression(new VariableExpression("x"), new VariableExpression("y"));
            Value = exp.Interpret(ctx);
            Console.WriteLine(Value); // expected: False

            exp = new AndExpression(new VariableExpression("z"), new VariableExpression("y"));
            Value = exp.Interpret(ctx);
            Console.WriteLine(Value); // expected: False
        }

        static void Main(string[] args)
        {
            test_1();

            Console.Read();
        }
    }
}
