using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class V5 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Discipline",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    DatumOdKadaPostoji = table.Column<DateTime>(type: "datetime2", nullable: false),
                    BrojTakmicara = table.Column<int>(type: "int", nullable: false),
                    Opis = table.Column<string>(type: "nvarchar(max)", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Discipline", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Sportisti",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Ime = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    Prezime = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    Pol = table.Column<string>(type: "nvarchar(1)", nullable: false),
                    DatumRodjenja = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Sportisti", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Sportovi",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    PojavioSe = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Sportovi", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Rekordi",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Takmicenje = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    OstvarenDana = table.Column<DateTime>(type: "datetime2", nullable: false),
                    SportistaID = table.Column<int>(type: "int", nullable: true),
                    DisciplinaID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Rekordi", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Rekordi_Discipline_DisciplinaID",
                        column: x => x.DisciplinaID,
                        principalTable: "Discipline",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Rekordi_Sportisti_SportistaID",
                        column: x => x.SportistaID,
                        principalTable: "Sportisti",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "SportSportista",
                columns: table => new
                {
                    SportisteID = table.Column<int>(type: "int", nullable: false),
                    SportoviID = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_SportSportista", x => new { x.SportisteID, x.SportoviID });
                    table.ForeignKey(
                        name: "FK_SportSportista_Sportisti_SportisteID",
                        column: x => x.SportisteID,
                        principalTable: "Sportisti",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_SportSportista_Sportovi_SportoviID",
                        column: x => x.SportoviID,
                        principalTable: "Sportovi",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Rekordi_DisciplinaID",
                table: "Rekordi",
                column: "DisciplinaID");

            migrationBuilder.CreateIndex(
                name: "IX_Rekordi_SportistaID",
                table: "Rekordi",
                column: "SportistaID");

            migrationBuilder.CreateIndex(
                name: "IX_SportSportista_SportoviID",
                table: "SportSportista",
                column: "SportoviID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Rekordi");

            migrationBuilder.DropTable(
                name: "SportSportista");

            migrationBuilder.DropTable(
                name: "Discipline");

            migrationBuilder.DropTable(
                name: "Sportisti");

            migrationBuilder.DropTable(
                name: "Sportovi");
        }
    }
}
