using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Text;

namespace IMMRequest.DataAccess.Interfaces
{
    public interface IRepository<T> where T : class
    {
        void Add(T entity);
        void Delete(T entity);
        void Update(T entity);
        bool Exists(Expression<Func<T, bool>> predicate);
        IEnumerable<T> GetAll();
        IEnumerable<T> Get(Expression<Func<T, bool>> predicate);
        T FirstOrDefault(Expression<Func<T, bool>> predicate);
        void Save();
    }
}
