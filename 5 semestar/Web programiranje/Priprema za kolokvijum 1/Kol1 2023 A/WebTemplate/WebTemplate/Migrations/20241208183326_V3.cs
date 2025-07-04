﻿using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class V3 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Knjige_Autori_AutorID",
                table: "Knjige");

            migrationBuilder.AlterColumn<int>(
                name: "AutorID",
                table: "Knjige",
                type: "int",
                nullable: true,
                oldClrType: typeof(int),
                oldType: "int");

            migrationBuilder.AddForeignKey(
                name: "FK_Knjige_Autori_AutorID",
                table: "Knjige",
                column: "AutorID",
                principalTable: "Autori",
                principalColumn: "ID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Knjige_Autori_AutorID",
                table: "Knjige");

            migrationBuilder.AlterColumn<int>(
                name: "AutorID",
                table: "Knjige",
                type: "int",
                nullable: false,
                defaultValue: 0,
                oldClrType: typeof(int),
                oldType: "int",
                oldNullable: true);

            migrationBuilder.AddForeignKey(
                name: "FK_Knjige_Autori_AutorID",
                table: "Knjige",
                column: "AutorID",
                principalTable: "Autori",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
