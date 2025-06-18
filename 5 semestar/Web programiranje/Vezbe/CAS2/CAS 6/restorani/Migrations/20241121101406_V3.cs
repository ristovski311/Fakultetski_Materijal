using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace restorani.Migrations
{
    /// <inheritdoc />
    public partial class V3 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_JeloSastojak_Jela_JeloID",
                table: "JeloSastojak");

            migrationBuilder.DropForeignKey(
                name: "FK_JeloSastojak_Sastojci_SastojakID",
                table: "JeloSastojak");

            migrationBuilder.DropPrimaryKey(
                name: "PK_JeloSastojak",
                table: "JeloSastojak");

            migrationBuilder.RenameTable(
                name: "JeloSastojak",
                newName: "Recept");

            migrationBuilder.RenameIndex(
                name: "IX_JeloSastojak_SastojakID",
                table: "Recept",
                newName: "IX_Recept_SastojakID");

            migrationBuilder.RenameIndex(
                name: "IX_JeloSastojak_JeloID",
                table: "Recept",
                newName: "IX_Recept_JeloID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_Recept",
                table: "Recept",
                column: "ID");

            migrationBuilder.AddForeignKey(
                name: "FK_Recept_Jela_JeloID",
                table: "Recept",
                column: "JeloID",
                principalTable: "Jela",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Recept_Sastojci_SastojakID",
                table: "Recept",
                column: "SastojakID",
                principalTable: "Sastojci",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Recept_Jela_JeloID",
                table: "Recept");

            migrationBuilder.DropForeignKey(
                name: "FK_Recept_Sastojci_SastojakID",
                table: "Recept");

            migrationBuilder.DropPrimaryKey(
                name: "PK_Recept",
                table: "Recept");

            migrationBuilder.RenameTable(
                name: "Recept",
                newName: "JeloSastojak");

            migrationBuilder.RenameIndex(
                name: "IX_Recept_SastojakID",
                table: "JeloSastojak",
                newName: "IX_JeloSastojak_SastojakID");

            migrationBuilder.RenameIndex(
                name: "IX_Recept_JeloID",
                table: "JeloSastojak",
                newName: "IX_JeloSastojak_JeloID");

            migrationBuilder.AddPrimaryKey(
                name: "PK_JeloSastojak",
                table: "JeloSastojak",
                column: "ID");

            migrationBuilder.AddForeignKey(
                name: "FK_JeloSastojak_Jela_JeloID",
                table: "JeloSastojak",
                column: "JeloID",
                principalTable: "Jela",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_JeloSastojak_Sastojci_SastojakID",
                table: "JeloSastojak",
                column: "SastojakID",
                principalTable: "Sastojci",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
