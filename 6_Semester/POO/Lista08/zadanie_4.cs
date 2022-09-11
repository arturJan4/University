using System;
using System.Collections.Generic;


namespace zad3
{
    // vending machine for drinks
    public abstract class State
    {
        public virtual void WaitIdle()
        {
            throw new NotImplementedException("Invalid machine state.");
        }
        public virtual void PickNumber(int number)
        {
            throw new NotImplementedException("Invalid machine state.");
        }
        public virtual void PickBuyMethod(bool withCoins)
        {
            throw new NotImplementedException("Invalid machine state.");
        }
        public virtual void GiveMoney(double value = 0)
        {
            throw new NotImplementedException("Invalid machine state.");
        }
        public virtual void TakeChange()
        {
            throw new NotImplementedException("Invalid machine state.");
        }
        public virtual void TakeDrink()
        {
            throw new NotImplementedException("Invalid machine state.");
        }
        // doesn't make sense to implement without user input here
        // but would simply use inbuilt clock
        public virtual void TimeExceeded()
        {
            throw new NotImplementedException("Invalid machine state.");
        }
    }

    public class VendingMachine
    {
        public State state;
        private List<double> prices;
        public bool withCoins; // does user pay with coins or card
        public double inMachine = 0; // how much money is inside
        public double selectedPrice; // price of selected item

        public VendingMachine(List<double> prices)
        {
            this.prices = prices;
            this.state = new WaitIdleState(this);
        }

        public void SetState(State newState)
        {
            this.state = newState;
        }

        public double GetPrice(int number)
        {
            if (number >= prices.Count || number < 0)
            {
                throw new InvalidOperationException("There is drink of such number");
            }

            return this.prices[number];
        }

        public void WaitIdle()
        {
            state.WaitIdle();
        }
        public void PickNumber(int number)
        {
            state.PickNumber(number);
        }
        public void PickBuyMethod(bool withCoins)
        {
            state.PickBuyMethod(withCoins);
        }
        public void GiveMoney(double value = 0)
        {
            state.GiveMoney(value);
        }
        public void TakeChange()
        {
            state.TakeChange();
        }
        public void TakeDrink()
        {
            state.TakeDrink();
        }
        public void TimeExceeded()
        {
            state.TimeExceeded();
        }
    }

    public class WaitIdleState : State
    {
        VendingMachine machine;
        public WaitIdleState(VendingMachine m)
        {
            this.machine = m;
        }

        public override void PickNumber(int number)
        {
            this.machine.selectedPrice = machine.GetPrice(number);
            Console.WriteLine("Selected {0}, cost: {1}", number, this.machine.selectedPrice);

            machine.SetState(new BuyMethodState(this.machine));
        }
    }

    public class BuyMethodState : State
    {
        VendingMachine machine;
        public BuyMethodState(VendingMachine m)
        {
            this.machine = m;
        }

        public override void PickBuyMethod(bool withCoins)
        {
            machine.withCoins = withCoins;
            if (withCoins)
            {
                Console.WriteLine("Selected coins, insert coins:");
            }
            else
            {
                Console.WriteLine("Selected card");
            }
            machine.SetState(new PayingState(this.machine));
        }
    }

    public class PayingState : State
    {
        VendingMachine machine;
        public PayingState(VendingMachine m)
        {
            this.machine = m;
        }

        public override void GiveMoney(double value = 0)
        {
            if (value > 0 && !this.machine.withCoins)
            {
                throw new InvalidOperationException("Selected card and paying with coins");
            }

            if (this.machine.withCoins)
            {
                this.machine.inMachine += value;
                Console.WriteLine("Inserted {0} in coins", value);

                if (this.machine.inMachine == this.machine.selectedPrice)
                {
                    Console.WriteLine("Paid exact ammount. Giving out drink");
                    machine.SetState(new GivingDrinkState(this.machine));
                    return;
                }
                else if (this.machine.inMachine > this.machine.selectedPrice)
                {
                    Console.WriteLine("Paid more than ammount. Giving out {0} change", this.machine.inMachine - this.machine.selectedPrice);
                    machine.SetState(new GivingChangeState(this.machine));
                }
                else
                {
                    Console.WriteLine("Not enough coins. Need {0} more.", this.machine.selectedPrice - this.machine.inMachine);
                    return;
                }
            }
            else
            {
                Console.WriteLine("Paying with card...");
                Console.WriteLine("[Terminal: to pay: {0}] Swipe card!", this.machine.selectedPrice);
                machine.SetState(new GivingDrinkState(this.machine));
                return;
            }
        }
    }

    public class GivingChangeState : State
    {
        VendingMachine machine;
        public GivingChangeState(VendingMachine m)
        {
            this.machine = m;
        }

        public override void TakeChange()
        {
            this.machine.inMachine = 0;
            Console.WriteLine("Change taken. Get your drink!");

            machine.SetState(new GivingDrinkState(this.machine));
        }
    }

    public class GivingDrinkState : State
    {
        VendingMachine machine;
        public GivingDrinkState(VendingMachine m)
        {
            this.machine = m;
        }

        public override void TakeDrink()
        {
            Console.WriteLine("Drink taken.");

            machine.SetState(new WaitIdleState(this.machine));
        }
    }



    class Program
    {
        static void Test_automata()
        {
            List<double> prices = new List<double>(new double[] { 2.5, 1.4, 3.0, 5.0 });
            var vm = new VendingMachine(prices);

            // pay with coins and taking change
            vm.PickNumber(2);
            vm.PickBuyMethod(true);
            vm.GiveMoney(2);
            vm.GiveMoney(2);
            vm.TakeChange();
            vm.TakeDrink();

            // pay with coins exactly the ammount
            vm.PickNumber(2);
            vm.PickBuyMethod(true);
            vm.GiveMoney(3);
            vm.TakeDrink();


            // pay with card
            vm.PickNumber(2);
            vm.PickBuyMethod(false);
            vm.GiveMoney();
            vm.TakeDrink();
        }


        static void Main()
        {
            Test_automata();
            Console.ReadLine();
        }
    }
}
