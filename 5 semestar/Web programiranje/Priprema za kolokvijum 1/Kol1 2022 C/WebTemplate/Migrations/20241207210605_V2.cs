using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class V2 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Bolnice_Lekari_LekarID",
                table: "Bolnice");

            migrationBuilder.DropIndex(
                name: "IX_Bolnice_LekarID",
                table: "Bolnice");

            migrationBuilder.DropColumn(
                name: "LekarID",
                table: "Bolnice");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "LekarID",
                table: "Bolnice",
                type: "int",
                nullable: true);

            migrationBuilder.CreateIndex(
                name: "IX_Bolnice_LekarID",
                table: "Bolnice",
                column: "LekarID");

            migrationBuilder.AddForeignKey(
                name: "FK_Bolnice_Lekari_LekarID",
                table: "Bolnice",
                column: "LekarID",
                principalTable: "Lekari",
                principalColumn: "ID");
        }
    }
}
