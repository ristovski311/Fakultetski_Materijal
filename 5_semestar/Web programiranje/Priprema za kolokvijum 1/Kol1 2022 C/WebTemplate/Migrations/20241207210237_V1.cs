using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class V1 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Licence",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    DatumDobijanja = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Licence", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Lekari",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Ime = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Prezime = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    DatumRodjenja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    DatumDiplomiranja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    LicencaID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Lekari", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Lekari_Licence_LicencaID",
                        column: x => x.LicencaID,
                        principalTable: "Licence",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "Bolnice",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    Lokacija = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    BrojOdeljenja = table.Column<int>(type: "int", nullable: false),
                    BrojOsoblja = table.Column<int>(type: "int", nullable: false),
                    BrojTelefona = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    LekarID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Bolnice", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Bolnice_Lekari_LekarID",
                        column: x => x.LekarID,
                        principalTable: "Lekari",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "BolnicaLekari",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    LekarID = table.Column<int>(type: "int", nullable: true),
                    BolnicaID = table.Column<int>(type: "int", nullable: true),
                    DatumUgovora = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Specijalnost = table.Column<string>(type: "nvarchar(max)", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_BolnicaLekari", x => x.ID);
                    table.ForeignKey(
                        name: "FK_BolnicaLekari_Bolnice_BolnicaID",
                        column: x => x.BolnicaID,
                        principalTable: "Bolnice",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_BolnicaLekari_Lekari_LekarID",
                        column: x => x.LekarID,
                        principalTable: "Lekari",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateIndex(
                name: "IX_BolnicaLekari_BolnicaID",
                table: "BolnicaLekari",
                column: "BolnicaID");

            migrationBuilder.CreateIndex(
                name: "IX_BolnicaLekari_LekarID",
                table: "BolnicaLekari",
                column: "LekarID");

            migrationBuilder.CreateIndex(
                name: "IX_Bolnice_LekarID",
                table: "Bolnice",
                column: "LekarID");

            migrationBuilder.CreateIndex(
                name: "IX_Lekari_LicencaID",
                table: "Lekari",
                column: "LicencaID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "BolnicaLekari");

            migrationBuilder.DropTable(
                name: "Bolnice");

            migrationBuilder.DropTable(
                name: "Lekari");

            migrationBuilder.DropTable(
                name: "Licence");
        }
    }
}
