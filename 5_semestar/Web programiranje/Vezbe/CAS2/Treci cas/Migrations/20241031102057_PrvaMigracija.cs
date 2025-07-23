using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace DrugiCas.Migrations
{
    /// <inheritdoc />
    public partial class PrvaMigracija : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Gradovi",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Povrsina = table.Column<double>(type: "float", nullable: false),
                    BrojStanovnika = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Gradovi", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Sastojak",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    RokTrajanja = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Sastojak", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "TipRestorana",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TipRestorana", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Restorani",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    X = table.Column<double>(type: "float", nullable: false),
                    Y = table.Column<double>(type: "float", nullable: false),
                    TipID = table.Column<int>(type: "int", nullable: true),
                    UkupnaSumaOcena = table.Column<int>(type: "int", nullable: false),
                    BrojOcenjivanja = table.Column<int>(type: "int", nullable: false),
                    GradID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Restorani", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Restorani_Gradovi_GradID",
                        column: x => x.GradID,
                        principalTable: "Gradovi",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Restorani_TipRestorana_TipID",
                        column: x => x.TipID,
                        principalTable: "TipRestorana",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "Jelo",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Slika = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    KalorijskaVrednost = table.Column<int>(type: "int", nullable: true),
                    DaLiJeJelo = table.Column<bool>(type: "bit", nullable: false),
                    RestoranID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Jelo", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Jelo_Restorani_RestoranID",
                        column: x => x.RestoranID,
                        principalTable: "Restorani",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "JeloSastojak",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    JeloID = table.Column<int>(type: "int", nullable: false),
                    SastojakID = table.Column<int>(type: "int", nullable: false),
                    Kolicina = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_JeloSastojak", x => x.ID);
                    table.ForeignKey(
                        name: "FK_JeloSastojak_Jelo_JeloID",
                        column: x => x.JeloID,
                        principalTable: "Jelo",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_JeloSastojak_Sastojak_SastojakID",
                        column: x => x.SastojakID,
                        principalTable: "Sastojak",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Jelo_RestoranID",
                table: "Jelo",
                column: "RestoranID");

            migrationBuilder.CreateIndex(
                name: "IX_JeloSastojak_JeloID",
                table: "JeloSastojak",
                column: "JeloID");

            migrationBuilder.CreateIndex(
                name: "IX_JeloSastojak_SastojakID",
                table: "JeloSastojak",
                column: "SastojakID");

            migrationBuilder.CreateIndex(
                name: "IX_Restorani_GradID",
                table: "Restorani",
                column: "GradID");

            migrationBuilder.CreateIndex(
                name: "IX_Restorani_TipID",
                table: "Restorani",
                column: "TipID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "JeloSastojak");

            migrationBuilder.DropTable(
                name: "Jelo");

            migrationBuilder.DropTable(
                name: "Sastojak");

            migrationBuilder.DropTable(
                name: "Restorani");

            migrationBuilder.DropTable(
                name: "Gradovi");

            migrationBuilder.DropTable(
                name: "TipRestorana");
        }
    }
}
