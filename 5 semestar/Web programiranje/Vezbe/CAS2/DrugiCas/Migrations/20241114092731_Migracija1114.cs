using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace DrugiCas.Migrations
{
    /// <inheritdoc />
    public partial class Migracija1114 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<double>(
                name: "Prihodi",
                table: "Restorani",
                type: "float",
                nullable: false,
                defaultValue: 0.0);

            migrationBuilder.AddColumn<double>(
                name: "Rashodi",
                table: "Restorani",
                type: "float",
                nullable: false,
                defaultValue: 0.0);

            migrationBuilder.AlterColumn<string>(
                name: "Naziv",
                table: "Gradovi",
                type: "nvarchar(50)",
                maxLength: 50,
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(max)");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Prihodi",
                table: "Restorani");

            migrationBuilder.DropColumn(
                name: "Rashodi",
                table: "Restorani");

            migrationBuilder.AlterColumn<string>(
                name: "Naziv",
                table: "Gradovi",
                type: "nvarchar(max)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(50)",
                oldMaxLength: 50);
        }
    }
}
