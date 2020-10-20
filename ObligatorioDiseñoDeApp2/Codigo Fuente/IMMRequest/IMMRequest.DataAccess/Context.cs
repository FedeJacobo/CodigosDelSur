using IMMRequest.Entities;
using Microsoft.EntityFrameworkCore;

namespace IMMRequest.DataAccess
{
    public class Context : DbContext
    {
        public DbSet<UserEntity> Users { get; set; }
        public DbSet<RequestEntity> Requests { get; set; }
        public DbSet<TypeReqEntity> TypeReqs { get; set; }
        public DbSet<AdditionalFieldEntity> AdditionalFields { get; set; }
        public DbSet<AreaEntity> Areas { get; set; }
        public DbSet<TopicEntity> Topics { get; set; }
        public DbSet<SessionEntity> Sessions { get; set; } 
        
        public Context(DbContextOptions<Context> options) : base(options)
        {

        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            modelBuilder.Entity<UserEntity>().HasKey(u => u.Id);
            modelBuilder.Entity<UserEntity>().Property(u => u.Id).ValueGeneratedOnAdd();
            modelBuilder.Entity<UserEntity>().Property(u => u.CompleteName).IsRequired();
            modelBuilder.Entity<UserEntity>().Property(u => u.Mail).IsRequired();
            modelBuilder.Entity<UserEntity>().Property(u => u.Password).IsRequired();
            modelBuilder.Entity<UserEntity>().Property(u => u.IsAdmin).IsRequired();
            modelBuilder.Entity<UserEntity>().HasMany(u => u.Requests);
            modelBuilder.Entity<UserEntity>().Property(u => u.IsDeleted).IsRequired();

            modelBuilder.Entity<RequestEntity>().HasKey(u => u.Id);
            modelBuilder.Entity<RequestEntity>().Property(u => u.Id).ValueGeneratedOnAdd();
            modelBuilder.Entity<RequestEntity>().Property(u => u.Detail).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.ApplicantName).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.Mail).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.Phone);
            modelBuilder.Entity<RequestEntity>().Property(u => u.Status).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.StatusDetail).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.AdditionalFieldsValues).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.AreaName).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.TopicName).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.TypeName).IsRequired();
            modelBuilder.Entity<RequestEntity>().Property(u => u.Date).IsRequired();

            modelBuilder.Entity<TypeReqEntity>().HasKey(u => u.Id);
            modelBuilder.Entity<TypeReqEntity>().Property(u => u.Id).ValueGeneratedOnAdd();
            modelBuilder.Entity<TypeReqEntity>().Property(u => u.Name).IsRequired();
            modelBuilder.Entity<TypeReqEntity>().Property(u => u.IsDeleted).IsRequired();
            modelBuilder.Entity<TypeReqEntity>().Property(u => u.TopicEntityId).IsRequired();

            modelBuilder.Entity<AdditionalFieldEntity>().HasKey(u => u.Id);
            modelBuilder.Entity<AdditionalFieldEntity>().Property(u => u.Id).ValueGeneratedOnAdd();
            modelBuilder.Entity<AdditionalFieldEntity>().Property(u => u.Name).IsRequired();
            modelBuilder.Entity<AdditionalFieldEntity>().Property(u => u.Type).IsRequired();
            modelBuilder.Entity<AdditionalFieldEntity>().Property(u => u.Range).IsRequired();
            modelBuilder.Entity<AdditionalFieldEntity>().Property(u => u.IsDeleted).IsRequired();

            modelBuilder.Entity<AreaEntity>().HasKey(u => u.Id);
            modelBuilder.Entity<AreaEntity>().Property(u => u.Id).ValueGeneratedOnAdd();
            modelBuilder.Entity<AreaEntity>().Property(u => u.Name).IsRequired();
            modelBuilder.Entity<AreaEntity>().HasMany(u => u.Topics);
            

            modelBuilder.Entity<TopicEntity>().HasKey(u => u.Id);
            modelBuilder.Entity<TopicEntity>().Property(u => u.Id).ValueGeneratedOnAdd();
            modelBuilder.Entity<TopicEntity>().Property(u => u.Name).IsRequired();
            modelBuilder.Entity<TopicEntity>().HasMany(u => u.RequestTypes);
        }
    }
}
