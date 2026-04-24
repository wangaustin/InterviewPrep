using GameStore.Api.Data;
using GameStore.Api.Dtos;
using GameStore.Api.Endpoints;


var builder = WebApplication.CreateBuilder(args);

const string VueCorsPolicy = "VueDevClient";

builder.Services.AddCors(options =>
{
    options.AddPolicy(VueCorsPolicy, policy =>
    {
        policy
            .WithOrigins("http://localhost:5173")
            .AllowAnyHeader()
            .AllowAnyMethod();
    });
});

builder.Services.AddValidation();
builder.AddGameStoreDb();

var app = builder.Build();

app.UseCors(VueCorsPolicy);

app.MapGamesEndpoints();
app.MapGenresEndpoints();

app.MigrateDb();

app.Run();
