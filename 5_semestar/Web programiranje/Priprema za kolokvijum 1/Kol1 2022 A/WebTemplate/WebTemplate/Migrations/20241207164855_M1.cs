using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class M1 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Aerodromi",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    Kod = table.Column<string>(type: "nvarchar(3)", maxLength: 3, nullable: false),
                    Lokacija = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    KapacitetLetelica = table.Column<int>(type: "int", nullable: false),
                    KapacitetPutnika = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Aerodromi", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Letelice",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naziv = table.Column<string>(type: "nvarchar(50)", maxLength: 50, nullable: false),
                    KapacitetPutnika = table.Column<int>(type: "int", nullable: false),
                    BrojOsoblja = table.Column<int>(type: "int", nullable: false),
                    BrojMotora = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Letelice", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "Relacije",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    AerodromOdID = table.Column<int>(type: "int", nullable: true),
                    AerodromDoID = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Relacije", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Relacije_Aerodromi_AerodromDoID",
                        column: x => x.AerodromDoID,
                        principalTable: "Aerodromi",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Relacije_Aerodromi_AerodromOdID",
                        column: x => x.AerodromOdID,
                        principalTable: "Aerodromi",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "Letovi",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    RelacijaID = table.Column<int>(type: "int", nullable: false),
                    LetelicaID = table.Column<int>(type: "int", nullable: true),
                    BrojPutnika = table.Column<int>(type: "int", nullable: false),
                    VremePoletanja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    VremeSletanja = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Letovi", x => x.ID);
                    table.ForeignKey(
                        name: "FK_Letovi_Letelice_LetelicaID",
                        column: x => x.LetelicaID,
                        principalTable: "Letelice",
                        principalColumn: "ID");
                    table.ForeignKey(
                        name: "FK_Letovi_Relacije_RelacijaID",
                        column: x => x.RelacijaID,
                        principalTable: "Relacije",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Letovi_LetelicaID",
                table: "Letovi",
                column: "LetelicaID");

            migrationBuilder.CreateIndex(
                name: "IX_Letovi_RelacijaID",
                table: "Letovi",
                column: "RelacijaID");

            migrationBuilder.CreateIndex(
                name: "IX_Relacije_AerodromDoID",
                table: "Relacije",
                column: "AerodromDoID");

            migrationBuilder.CreateIndex(
                name: "IX_Relacije_AerodromOdID",
                table: "Relacije",
                column: "AerodromOdID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Letovi");

            migrationBuilder.DropTable(
                name: "Letelice");

            migrationBuilder.DropTable(
                name: "Relacije");

            migrationBuilder.DropTable(
                name: "Aerodromi");
        }
    }
}
