using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace EFCore1.Migrations
{
    /// <inheritdoc />
    public partial class AddAuthorName : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropPrimaryKey(
                name: "PK_T_Books",
                table: "T_Books");

            migrationBuilder.RenameTable(
                name: "T_Books",
                newName: "T Books");

            migrationBuilder.AlterColumn<string>(
                name: "Title",
                table: "T Books",
                type: "nvarchar(50)",
                maxLength: 50,
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(max)");

            migrationBuilder.AddColumn<string>(
                name: "AuthorName",
                table: "T Books",
                type: "nvarchar(20)",
                maxLength: 20,
                nullable: false,
                defaultValue: "");

            migrationBuilder.AddPrimaryKey(
                name: "PK_T Books",
                table: "T Books",
                column: "Id");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropPrimaryKey(
                name: "PK_T Books",
                table: "T Books");

            migrationBuilder.DropColumn(
                name: "AuthorName",
                table: "T Books");

            migrationBuilder.RenameTable(
                name: "T Books",
                newName: "T_Books");

            migrationBuilder.AlterColumn<string>(
                name: "Title",
                table: "T_Books",
                type: "nvarchar(max)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(50)",
                oldMaxLength: 50);

            migrationBuilder.AddPrimaryKey(
                name: "PK_T_Books",
                table: "T_Books",
                column: "Id");
        }
    }
}
