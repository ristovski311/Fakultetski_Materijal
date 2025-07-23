using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace restorani.Migrations
{
    /// <inheritdoc />
    public partial class V2 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Magacin_Restorani_RestoranID",
                table: "Magacin");

            migrationBuilder.DropForeignKey(
                name: "FK_Magacin_Sastojci_SastojakID",
                table: "Magacin");

            migrationBuilder.DropPrimaryKey(
                name: "PK_Magacin",
                table: "Magacin");

            migrationBuilder.RenameTable(
                name: "Magacin",
                newName: "MagaciniRestorana");

            migrationBuilder.RenameIndex(
                name: "IX_Magacin_SastojakID",
                table: "MagaciniRestorana",
                newName: "IX_MagaciniRestorana_SastojakID");

            migrationBuilder.RenameIndex(
                name: "IX_Magacin_RestoranID",
                table: "MagaciniRestorana",
                newName: "IX_MagaciniRestorana_RestoranID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_MagaciniRestorana",
                table: "MagaciniRestorana",
                column: "Id");

            migrationBuilder.AddForeignKey(
                name: "FK_MagaciniRestorana_Restorani_RestoranID",
                table: "MagaciniRestorana",
                column: "RestoranID",
                principalTable: "Restorani",
                principalColumn: "ID");

            migrationBuilder.AddForeignKey(
                name: "FK_MagaciniRestorana_Sastojci_SastojakID",
                table: "MagaciniRestorana",
                column: "SastojakID",
                principalTable: "Sastojci",
                principalColumn: "ID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_MagaciniRestorana_Restorani_RestoranID",
                table: "MagaciniRestorana");

            migrationBuilder.DropForeignKey(
                name: "FK_MagaciniRestorana_Sastojci_SastojakID",
                table: "MagaciniRestorana");

            migrationBuilder.DropPrimaryKey(
                name: "PK_MagaciniRestorana",
                table: "MagaciniRestorana");

            migrationBuilder.RenameTable(
                name: "MagaciniRestorana",
                newName: "Magacin");

            migrationBuilder.RenameIndex(
                name: "IX_MagaciniRestorana_SastojakID",
                table: "Magacin",
                newName: "IX_Magacin_SastojakID");

            migrationBuilder.RenameIndex(
                name: "IX_MagaciniRestorana_RestoranID",
                table: "Magacin",
                newName: "IX_Magacin_RestoranID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_Magacin",
                table: "Magacin",
                column: "Id");

            migrationBuilder.AddForeignKey(
                name: "FK_Magacin_Restorani_RestoranID",
                table: "Magacin",
                column: "RestoranID",
                principalTable: "Restorani",
                principalColumn: "ID");

            migrationBuilder.AddForeignKey(
                name: "FK_Magacin_Sastojci_SastojakID",
                table: "Magacin",
                column: "SastojakID",
                principalTable: "Sastojci",
                principalColumn: "ID");
        }
    }
}
