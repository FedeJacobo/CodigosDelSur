using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.BusinessLogic
{
    public class AreaLogic : IAreaLogic
    {
        private readonly IUnitOfWork unitOfWork;
        public AreaLogic(IUnitOfWork unitOfWork)
        {
            this.unitOfWork = unitOfWork;
        }

        public int Add(AreaEntity area)
        {
            ValidateAreaIdExistance(area.Id);
            CheckTopicsNull(area);
            unitOfWork.AreaRepository.Add(area);
            unitOfWork.Save();
            return unitOfWork.AreaRepository.FirstOrDefault(a => a.Name == area.Name).Id;
        }

        private static void CheckTopicsNull(AreaEntity area)
        {
            if (area.Topics == null)
            {
                area.Topics = new List<TopicEntity>();
            }
        }

        private void ValidateAreaIdExistance(int id)
        {
            if (unitOfWork.AreaRepository.Exists(a => a.Id == id))
                throw new ArgumentException($"Area with id: {id} already exist");
        }

        public IEnumerable<AreaEntity> GetAll()
        {
            IEnumerable<AreaEntity> areasResult = unitOfWork.AreaRepository.GetAll();
            return areasResult;
        }

        public AreaEntity GetByName(string name)
        {
            ValidateAreaNameExistance(name);
            AreaEntity result = unitOfWork.AreaRepository.FirstOrDefault(u => u.Name == name);
            return result;
        }

        private void ValidateAreaNameExistance(string name)
        {
            if (!unitOfWork.AreaRepository.Exists(a => a.Name == name))
                throw new ArgumentException($"Area with name: {name} doesn't exist");
        }
    }
}
