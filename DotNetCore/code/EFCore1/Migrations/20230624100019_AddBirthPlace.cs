using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace EFCore1.Migrations
{
    /// <inheritdoc />
    public partial class AddBirthPlace : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "BirthPlaceP",
                table: "T_Persons",
                type: "nvarchar(max)",
                nullable: false,
                defaultValue: "");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "BirthPlaceP",
                table: "T_Persons");
        }
    }
}
