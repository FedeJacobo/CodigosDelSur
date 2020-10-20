using System;
using Microsoft.EntityFrameworkCore.Migrations;

namespace IMMRequest.DataAccess.Migrations
{
    public partial class IMMRequestDataBase : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Areas",
                columns: table => new
                {
                    Id = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Areas", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Sessions",
                columns: table => new
                {
                    Id = table.Column<Guid>(nullable: false),
                    Token = table.Column<Guid>(nullable: false),
                    AdminId = table.Column<int>(nullable: false),
                    Mail = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Sessions", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Users",
                columns: table => new
                {
                    Id = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    CompleteName = table.Column<string>(nullable: false),
                    Mail = table.Column<string>(nullable: false),
                    Password = table.Column<string>(nullable: false),
                    IsAdmin = table.Column<bool>(nullable: false),
                    IsDeleted = table.Column<bool>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Users", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Topics",
                columns: table => new
                {
                    Id = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(nullable: false),
                    AreaEntityId = table.Column<int>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Topics", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Topics_Areas_AreaEntityId",
                        column: x => x.AreaEntityId,
                        principalTable: "Areas",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "Requests",
                columns: table => new
                {
                    Id = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Detail = table.Column<string>(nullable: false),
                    ApplicantName = table.Column<string>(nullable: false),
                    Mail = table.Column<string>(nullable: false),
                    Phone = table.Column<string>(nullable: true),
                    RequestTypeEntityId = table.Column<int>(nullable: false),
                    Status = table.Column<string>(nullable: false),
                    StatusDetail = table.Column<string>(nullable: false),
                    AdditionalFieldsValues = table.Column<string>(nullable: false),
                    AreaName = table.Column<string>(nullable: false),
                    TopicName = table.Column<string>(nullable: false),
                    TypeName = table.Column<string>(nullable: false),
                    Date = table.Column<DateTime>(nullable: false),
                    UserEntityId = table.Column<int>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Requests", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Requests_Users_UserEntityId",
                        column: x => x.UserEntityId,
                        principalTable: "Users",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateTable(
                name: "TypeReqs",
                columns: table => new
                {
                    Id = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(nullable: false),
                    TopicEntityId = table.Column<int>(nullable: false),
                    IsDeleted = table.Column<bool>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TypeReqs", x => x.Id);
                    table.ForeignKey(
                        name: "FK_TypeReqs_Topics_TopicEntityId",
                        column: x => x.TopicEntityId,
                        principalTable: "Topics",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "AdditionalFields",
                columns: table => new
                {
                    Id = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(nullable: false),
                    Type = table.Column<string>(nullable: false),
                    Range = table.Column<string>(nullable: false),
                    TypeReqEntityId = table.Column<int>(nullable: false),
                    IsDeleted = table.Column<bool>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_AdditionalFields", x => x.Id);
                    table.ForeignKey(
                        name: "FK_AdditionalFields_TypeReqs_TypeReqEntityId",
                        column: x => x.TypeReqEntityId,
                        principalTable: "TypeReqs",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_AdditionalFields_TypeReqEntityId",
                table: "AdditionalFields",
                column: "TypeReqEntityId");

            migrationBuilder.CreateIndex(
                name: "IX_Requests_UserEntityId",
                table: "Requests",
                column: "UserEntityId");

            migrationBuilder.CreateIndex(
                name: "IX_Topics_AreaEntityId",
                table: "Topics",
                column: "AreaEntityId");

            migrationBuilder.CreateIndex(
                name: "IX_TypeReqs_TopicEntityId",
                table: "TypeReqs",
                column: "TopicEntityId");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "AdditionalFields");

            migrationBuilder.DropTable(
                name: "Requests");

            migrationBuilder.DropTable(
                name: "Sessions");

            migrationBuilder.DropTable(
                name: "TypeReqs");

            migrationBuilder.DropTable(
                name: "Users");

            migrationBuilder.DropTable(
                name: "Topics");

            migrationBuilder.DropTable(
                name: "Areas");
        }
    }
}
