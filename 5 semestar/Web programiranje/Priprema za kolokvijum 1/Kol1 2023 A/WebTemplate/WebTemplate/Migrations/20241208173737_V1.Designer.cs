﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using WebTemplate.Models;

#nullable disable

namespace WebTemplate.Migrations
{
    [DbContext(typeof(IspitContext))]
    [Migration("20241208173737_V1")]
    partial class V1
    {
        /// <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "8.0.0")
                .HasAnnotation("Relational:MaxIdentifierLength", 128);

            SqlServerModelBuilderExtensions.UseIdentityColumns(modelBuilder);

            modelBuilder.Entity("WebTemplate.Models.Autor", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<DateTime>("DatumRodjenja")
                        .HasColumnType("datetime2");

                    b.Property<string>("Ime")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Pol")
                        .IsRequired()
                        .HasColumnType("nvarchar(1)");

                    b.Property<string>("Prezime")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("ID");

                    b.ToTable("Autori");
                });

            modelBuilder.Entity("WebTemplate.Models.IzdavackaKuca", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<string>("Drzava")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Naziv")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("ID");

                    b.ToTable("IzdavackeKuce");
                });

            modelBuilder.Entity("WebTemplate.Models.Knjiga", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<int>("AutorID")
                        .HasColumnType("int");

                    b.Property<int>("BrojStranica")
                        .HasColumnType("int");

                    b.Property<DateTime?>("DatumObjavljivanja")
                        .HasColumnType("datetime2");

                    b.Property<string>("ISBN")
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Naslov")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Zanr")
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("ID");

                    b.HasIndex("AutorID");

                    b.ToTable("Knjige");
                });

            modelBuilder.Entity("WebTemplate.Models.Ugovor", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("ID"));

                    b.Property<int?>("AutorID")
                        .HasColumnType("int");

                    b.Property<DateTime>("DatumPotpisa")
                        .HasColumnType("datetime2");

                    b.Property<int?>("IzdavackaKucaID")
                        .HasColumnType("int");

                    b.Property<int?>("KnjigaID")
                        .HasColumnType("int");

                    b.HasKey("ID");

                    b.HasIndex("AutorID");

                    b.HasIndex("IzdavackaKucaID");

                    b.HasIndex("KnjigaID");

                    b.ToTable("Ugovori");
                });

            modelBuilder.Entity("WebTemplate.Models.Knjiga", b =>
                {
                    b.HasOne("WebTemplate.Models.Autor", "Autor")
                        .WithMany("Knjige")
                        .HasForeignKey("AutorID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Autor");
                });

            modelBuilder.Entity("WebTemplate.Models.Ugovor", b =>
                {
                    b.HasOne("WebTemplate.Models.Autor", "Autor")
                        .WithMany()
                        .HasForeignKey("AutorID");

                    b.HasOne("WebTemplate.Models.IzdavackaKuca", "IzdavackaKuca")
                        .WithMany()
                        .HasForeignKey("IzdavackaKucaID");

                    b.HasOne("WebTemplate.Models.Knjiga", "Knjiga")
                        .WithMany()
                        .HasForeignKey("KnjigaID");

                    b.Navigation("Autor");

                    b.Navigation("IzdavackaKuca");

                    b.Navigation("Knjiga");
                });

            modelBuilder.Entity("WebTemplate.Models.Autor", b =>
                {
                    b.Navigation("Knjige");
                });
#pragma warning restore 612, 618
        }
    }
}
