namespace EFCore1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // ctx 相当于逻辑上的数据库
            using (MyDbContext ctx = new MyDbContext())
            {
                //Person p = new Person();
                //p.Name = "Trump";
                //p.BirthPlaceP = "单独";
                //p.Age = 23;
                //ctx.Persons.Add(p);  // 把数据加入 Persons 这个逻辑的表里面

                //Book b1 = new Book
                //{
                //    AuthorName = "zsm",
                //    Price = 12,
                //    PubTime = DateTime.Now,
                //    Title = "Hekdhak"
                //};
                //Book b2 = new Book
                //{
                //    AuthorName = "dfs",
                //    Price = 143,
                //    PubTime = DateTime.Now,
                //    Title = "C语言"
                //};
                //Book b3 = new Book
                //{
                //    AuthorName = "Tom",
                //    Price = 324,
                //    PubTime = DateTime.Now,
                //    Title = "牛逼克拉斯"
                //};
                //ctx.Add(b1);
                //ctx.Add(b2);
                //ctx.Add(b3);

                //var books = ctx.Books.Where(b => b.Price > 80);
                //foreach (var book in books)
                //{
                //    Console.WriteLine(book.Title);
                //}
                //var book = ctx.Books.Single(b => b.Title == "C语言");
                //Console.WriteLine(book.Id + " " + book.Title + " " + book.Price);
                //IEnumerable<Book> books = ctx.Books.OrderByDescending(b => b.Price);
                //foreach (var book in books)
                //{
                //    Console.WriteLine(book.Title);
                //}

                //var book = ctx.Books.Single(b => b.Title == "C语言");
                //book.AuthorName = "ZSM";

                var book = ctx.Books.Single(b => b.Id == 2);
                ctx.Books.Remove(book);
                ctx.SaveChanges();  // 相当于 Update-Databse
            }
        }
    }
}