//namespace HelloWorld
//{
//    internal class Program
//    {
//        static unsafe void Main(string[] args)
//        {
//            Student stu = new Student(1, "");
//            Console.WriteLine(stu.ID);
//            Console.WriteLine(stu.Name == null);
//            double d = 100d;
//            stu.Add(100, 300);
//        }
//    }
//    class Student
//    {
//        public int Add(int a, int b)
//        {
//            return this.Add1(a, b);
//        }
//        public int Add1(int a, int b)
//        {
//            return a + b;
//        }
//        public Student()
//        {
//            this.ID = 1;
//            this.Name = "";
//        }
//        public Student(int id, string name)
//        {
//            this.ID = id;
//            this.Name = name;
//        }
//        public int ID;
//        public string Name;
//    }
//}

namespace HelloWorld
{
    internal class Program
    {
        static unsafe void Main(string[] args)
        {
            //Person a = new Person();
            //Person b = new Person();
            //a.Name = "Jack";
            //b.Name = "Marry";
            //List<Person> list = a + b;
            //foreach (var v in list)
            //{
            //    Console.WriteLine(v.Name);
            //}


            //Dictionary<string, Student> dic = new Dictionary<string, Student>();
            //for (int i = 1; i <= 10; i++)
            //{
            //    Student stu = new Student();
            //    stu.Name = "stu_" + i;
            //    stu.Score = 100 + i;
            //    dic.Add(stu.Name, stu);
            //}
            //Console.WriteLine(dic["stu_7"].Score);
            //Type t = typeof(int);
            //Console.WriteLine(t.Name);
            //Console.WriteLine(t.FullName);
            //Console.WriteLine(t.Namespace);
            //foreach (var m in t.GetMethods())
            //{
            //    Console.WriteLine(m.Name);
            //}


            //int x = default(int);
            //double d = default(double);
            //int y = default;
            //Console.WriteLine(x);
            //Console.WriteLine(y);
            //Console.WriteLine(d);


            //var v = "d";
            //Console.WriteLine(v.GetType().Name);
            //var p = new { Name = "Jack" , Age = 12};
            //Console.WriteLine(p.Name);
            //Console.WriteLine(p.Age);
            //Console.WriteLine(p.GetType().Name);

            //Student stu = new Student();
            //CsStudent csStu = new CsStudent();
            //stu.Report();
            //csStu.Report();


            //uint x = uint.MaxValue;
            //Console.WriteLine(x);
            //Console.WriteLine(Convert.ToString(x, 2));
            //try
            //{
            //    uint x = uint.MaxValue;
            //    uint y = checked(x + 1);
            //    Console.WriteLine(y);
            //}
            //catch (OverflowException ex)
            //{
            //    Console.WriteLine("There's overflow");
            //}
            //checked
            //{
            //    uint x = uint.MaxValue;
            //    uint y = checked(x + 1);
            //}


            //Console.WriteLine(sizeof(Student));


            //Student s = new Student();
            //s.Name = "J";
            //s.Score = 99;
            //Console.WriteLine(s.Score);
            //Student* stu = &s;
            //stu->Score = 100;
            //Console.WriteLine(s.Score);
            //Console.WriteLine(stu->Score);


            //Student s = new Student();
            //s.Name = "J";
            //s.Score = 99;
            //Console.WriteLine(s.Score);
            //Student* stu = &s;
            //(*stu).Score = 100;
            //Console.WriteLine(s.Score);


            //Nullable<int> x = null;
            //x = 100;
            //Console.WriteLine(x);
            //Console.WriteLine(x.HasValue);

            //int ? x = 10;
            //int y = x ?? 1;
            //Console.WriteLine(y);




        }
    }
    class Person
    {
        public string Name;
        public static List<Person> operator +(Person a, Person b)
        {
            List<Person> list = new List<Person>();
            list.Add(a);
            list.Add(b);
            Person child = new Person();
            child.Name = a.Name + " & " + b.Name + "'s child";
            list.Add(child);
            return list;
        }
    }
    class Student
    {
        public void Report()
        {
            Console.WriteLine("I am a student");
        }
        public string Name;
        public int Score;
    }
    class CsStudent : Student
    {
        new public void Report()
        {
            Console.WriteLine("I am a CS student");
        }
    }
}