using IMMRequest.BusinessLogic;
using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Mapper;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

namespace IMMRequest.WebApi
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddControllers();
            services.AddDbContext<Context>(options => options.UseSqlServer(@"Server=.\SQLEXPRESS;Database=IMMRequestDataBase;
                Trusted_Connection=True;MultipleActiveResultSets=True;", b => b.MigrationsAssembly("IMMRequest.DataAccess")));

            services.AddCors(
                options =>
                {
                  options.AddPolicy(
                    "CorsPolicy",
                    builder => builder
                    .AllowAnyOrigin()
                    .AllowAnyMethod()
                    .AllowAnyHeader()
                );
              }
            );

            services.AddScoped<IWebApiMapper, WebApiMapper>();

            services.AddScoped<IUserLogic, UserLogic>();
            services.AddScoped<IRequestLogic, RequestLogic>();
            services.AddScoped<ITypeReqLogic, TypeReqLogic>();
            services.AddScoped<IAdditionalFieldLogic, AdditionalFieldLogic>();
            services.AddScoped<ISessionLogic, SessionLogic>();
            services.AddScoped<IAreaLogic, AreaLogic>();
            services.AddScoped<ITopicLogic, TopicLogic>();
            services.AddScoped<IImportLogic, ImportLogic>();

            services.AddScoped<IUnitOfWork, UnitOfWork>();

            services.AddScoped<IRepository<UserEntity>, Repository<UserEntity>>();
            services.AddScoped<IRepository<RequestEntity>, Repository<RequestEntity>>();
            services.AddScoped<IRepository<TypeReqEntity>, Repository<TypeReqEntity>>();
            services.AddScoped<IRepository<AdditionalFieldEntity>, Repository<AdditionalFieldEntity>>();
            services.AddScoped<IRepository<AreaEntity>, Repository<AreaEntity>>();
            services.AddScoped<IRepository<TopicEntity>, Repository<TopicEntity>>();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.UseHttpsRedirection();

            app.UseRouting();

            app.UseAuthorization();

            app.UseCors("CorsPolicy");

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllers();
            });
        }
    }
}
