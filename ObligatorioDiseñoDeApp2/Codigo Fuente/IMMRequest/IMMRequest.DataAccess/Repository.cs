using IMMRequest.DataAccess.Interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;

namespace IMMRequest.DataAccess
{
    public class Repository<T> : IRepository<T> where T : class
    {
        protected Context context;

        public Repository(Context dbContext)
        {
            this.context = dbContext;
        }

        private DbSet<T> Entities
        {
            get
            {
                return this.context.Set<T>();
            }
        }

        public void Add(T entity)
        {
            this.Entities.Add(entity);
            this.context.SaveChanges();
        }

        public void Delete(T entity)
        {
            this.Entities.Remove(entity);
            this.context.SaveChanges();
        }

        public void Update(T entity)
        {
            this.context.Update(entity);
            this.context.SaveChanges();
        }

        public bool Exists(Expression<Func<T, bool>> predicate)
        {
            return this.Entities.Any(predicate);
        }

        public virtual IEnumerable<T> GetAll()
        {
            return this.Entities.ToList();
        }

        public virtual IEnumerable<T> Get(Expression<Func<T, bool>> predicate)
        {
            return this.Entities.Where(predicate).ToList();
        }

        public virtual T FirstOrDefault(Expression<Func<T, bool>> predicate)
        {
            return this.Entities.Where(predicate).FirstOrDefault();
        }

        public void Save()
        {
            try
            {
                context.SaveChanges();
            }
            catch (DbUpdateException e)
            {
                throw new ArgumentException(e.Message);
            }
        }
    }
}
