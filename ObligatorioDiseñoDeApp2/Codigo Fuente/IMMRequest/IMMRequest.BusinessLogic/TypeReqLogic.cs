using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.BusinessLogic
{
    public class TypeReqLogic : ITypeReqLogic
    {
        private readonly IUnitOfWork unitOfWork;

        public TypeReqLogic(IUnitOfWork unitOfWork)
        {
            this.unitOfWork = unitOfWork;
        }

        public int Add(TypeReqEntity tr)
        {
            if (TypeExists(tr.Id))
                throw new ArgumentException($"Type with id: {tr.Id} already exist");
            if (!TopicExists(tr))
                throw new ArgumentException($"Topic does not exist");
            /*if(tr.TopicEntityId<1 || tr.TopicEntityId > 18)
                throw new ArgumentException($"Topic with id: {tr.TopicEntityId} does not exist");*/
            if (TypeNameExistsInTopic(tr))
                throw new ArgumentException($"There is already a type with name {tr.Name} in the topic with id: {tr.TopicEntityId}");
            unitOfWork.TypeReqRepository.Add(tr);
            unitOfWork.Save();
            return this.GetByName(tr.Name).Id;
        }

        private bool TopicExists(TypeReqEntity tr)
        {
            return this.unitOfWork.TopicRepository.Exists(t => t.Id == tr.TopicEntityId);
        }

        public void Delete(int id)
        {
            if (!unitOfWork.TypeReqRepository.Exists(a => !a.IsDeleted && a.Id == id))
                throw new ArgumentException($"Type with id: {id} doesn't exist");

            TypeReqEntity typeReqEntity = unitOfWork.TypeReqRepository.FirstOrDefault(tr => !tr.IsDeleted && tr.Id == id);
            typeReqEntity.IsDeleted = true;
            unitOfWork.TypeReqRepository.Update(typeReqEntity);

            List<AdditionalFieldEntity> aF = GetAdditionalFieldFromType(typeReqEntity.Id);
            foreach (var a in aF)
            {
                a.IsDeleted = true;
                unitOfWork.AdditionalFieldRepository.Update(a);
            }

            unitOfWork.Save();
        }

        private List<AdditionalFieldEntity> GetAdditionalFieldFromType(int id)
        {
            return unitOfWork.AdditionalFieldRepository.Get(a => a.TypeReqEntityId == id && !a.IsDeleted).ToList();
        }

        public IEnumerable<TypeReqEntity> GetAll()
        {
            return unitOfWork.TypeReqRepository.GetAll().Where(tr => !tr.IsDeleted).ToList();
        }

        public TypeReqEntity GetById(int id)
        {
            if (!TypeExists(id))
                throw new ArgumentException($"Type with Id: {id} doesn't exist");

            TypeReqEntity ret = unitOfWork.TypeReqRepository.FirstOrDefault(u => u.Id == id && !u.IsDeleted);
            return ret;
        }

        public TypeReqEntity GetByName(string name)
        {
            if (!TypeNameExists(name))
                throw new ArgumentException($"Type with name: {name} doesn't exist");

            TypeReqEntity ret = unitOfWork.TypeReqRepository.FirstOrDefault(u => u.Name == name && !u.IsDeleted);
            return ret;
        }

        public void Update(TypeReqEntity tr)
        {
            if (!TypeExists(tr.Id))
                throw new ArgumentException($"Type with id: {tr.Id} doesn't exist");

            TypeReqEntity trToUpdate = unitOfWork.TypeReqRepository.FirstOrDefault(u => u.Id == tr.Id && !tr.IsDeleted);
            trToUpdate.Name = tr.Name;
            if (tr.AdditionalFields == null)
            {
                tr.AdditionalFields = new List<AdditionalFieldEntity>();
            }
            unitOfWork.TypeReqRepository.Update(trToUpdate);
            unitOfWork.Save();
        }

        public IEnumerable<AdditionalFieldEntity> GetAdditionalFields(int typeId)
        {
            if (!TypeExists(typeId))
                throw new ArgumentException($"Type with id: {typeId} doesn't exist");
            List<AdditionalFieldEntity> result = new List<AdditionalFieldEntity>();
            IEnumerable<AdditionalFieldEntity> addFEntities = unitOfWork.AdditionalFieldRepository.GetAll().Where(add => !add.IsDeleted);
            foreach (var entity in addFEntities)
            {
                TypeReqEntity typeReqEntity = unitOfWork.TypeReqRepository.FirstOrDefault(u => u.Id.Equals(entity.TypeReqEntityId) && !u.IsDeleted);
                if (typeReqEntity != null && typeId == typeReqEntity.Id)
                {
                    result.Add(entity);
                }
            }
            return result;
        }

        private bool TypeExists(int id)
        {
            return unitOfWork.TypeReqRepository.Exists(a => a.Id == id && !a.IsDeleted);
        }

        private bool TypeNameExists(string name)
        {
            return unitOfWork.TypeReqRepository.Exists(a => a.Name == name && !a.IsDeleted);
        }

        private bool TypeNameExistsInTopic(TypeReqEntity tr)
        {
            return unitOfWork.TypeReqRepository.Exists(a => a.Name == tr.Name && !a.IsDeleted && a.TopicEntityId == tr.TopicEntityId);
        }
    }
}
