using Microsoft.EntityFrameworkCore.Metadata.Builders;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EFCore1
{
    class BookConfig : IEntityTypeConfiguration<Book>
    {
        public void Configure(EntityTypeBuilder<Book> builder)
        {
            builder.ToTable("T Books");
            builder.Property(e => e.Title).HasMaxLength(50).IsRequired();
            builder.Property(e => e.AuthorName).HasMaxLength(20).IsRequired();
        }
    }
}
