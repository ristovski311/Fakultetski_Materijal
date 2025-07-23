using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace restorani.Migrations
{
    /// <inheritdoc />
    public partial class V1 : Migration
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
                    Naziv = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    Povrsina = table.Column<float>(type: "real", nullable: false),
                    BrojStanovnika = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Gradovi", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Sastojci",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Cena = table.Column<double>(type: "float", nullable: false),
                    RokTrajanja = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Sastojci", x => x.ID);
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
                    GradID = table.Column<int>(type: "int", nullable: true),
                    Prihodi = table.Column<double>(type: "float", nullable: false),
                    Rashodi = table.Column<double>(type: "float", nullable: false)
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
                name: "Jela",
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
                    table.PrimaryKey("PK_Jela", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Jela_Restorani_RestoranID",
                        column: x => x.RestoranID,
                        principalTable: "Restorani",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "Magacin",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    RestoranID = table.Column<int>(type: "int", nullable: true),
                    SastojakID = table.Column<int>(type: "int", nullable: true),
                    Kolicina = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Magacin", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Magacin_Restorani_RestoranID",
                        column: x => x.RestoranID,
                        principalTable: "Restorani",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Magacin_Sastojci_SastojakID",
                        column: x => x.SastojakID,
                        principalTable: "Sastojci",
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
                        name: "FK_JeloSastojak_Jela_JeloID",
                        column: x => x.JeloID,
                        principalTable: "Jela",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_JeloSastojak_Sastojci_SastojakID",
                        column: x => x.SastojakID,
                        principalTable: "Sastojci",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Jela_RestoranID",
                table: "Jela",
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
                name: "IX_Magacin_RestoranID",
                table: "Magacin",
                column: "RestoranID");

            migrationBuilder.CreateIndex(
                name: "IX_Magacin_SastojakID",
                table: "Magacin",
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
                name: "Magacin");

            migrationBuilder.DropTable(
                name: "Jela");

            migrationBuilder.DropTable(
                name: "Sastojci");

            migrationBuilder.DropTable(
                name: "Restorani");

            migrationBuilder.DropTable(
                name: "Gradovi");

            migrationBuilder.DropTable(
                name: "TipRestorana");
        }
    }
}
