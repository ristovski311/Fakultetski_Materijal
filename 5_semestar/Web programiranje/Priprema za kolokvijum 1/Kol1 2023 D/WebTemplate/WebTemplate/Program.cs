using Microsoft.EntityFrameworkCore;
using WebTemplate.Controllers;

var builder = WebApplication.CreateBuilder(args);

// Dodaj DbContext
builder.Services.AddDbContext<IspitContext>(options =>
{
    options.UseSqlServer(builder.Configuration.GetConnectionString("ProizvodiCS"));
});

// Dodaj kontrolere
builder.Services.AddControllers();

// Swagger (opciono za dev)
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

// 🚀 Globalni CORS – važi za sve zahteve i kontrolere
app.UseCors(policy =>
    policy.AllowAnyOrigin()
          .AllowAnyMethod()
          .AllowAnyHeader()
);

app.UseAuthorization();

app.MapControllers();

app.Run();
