BEGIN;
INSERT INTO config."AttributeDefinition" ("Id","GameConfigurationId","Designation","Description","MaximumValue")
VALUES ('8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06','00000001-0001-0000-0000-000000000000','Swell Life Ability Increase','',NULL);

CREATE TEMP TABLE swell_classes AS
SELECT DISTINCT r."CharacterClassId" AS cid
FROM config."AttributeRelationship" r
JOIN config."AttributeDefinition" a ON a."Id" = r."InputAttributeId"
WHERE a."Designation" = 'Swell Life Health Increase';

INSERT INTO config."AttributeRelationship"
  ("Id","TargetAttributeId","InputAttributeId","CharacterClassId","PowerUpDefinitionValueId","InputOperator","InputOperand","OperandAttributeId","AggregateType","SkillId","GameConfigurationId")
SELECT gen_random_uuid(), '466bbbba-c1d8-45dc-8832-2eaa1130acfd', '8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06', cid, NULL, 0, 1, NULL, 1, NULL, NULL
FROM swell_classes;

INSERT INTO config."ConstValueAttribute" ("Id","DefinitionId","CharacterClassId","Value","GameConfigurationId","AggregateType")
SELECT gen_random_uuid(), '8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06', cid, 1, NULL, 0
FROM swell_classes;

WITH v AS (
  INSERT INTO config."PowerUpDefinitionValue" ("Id","Value","AggregateType","MaximumValue")
  VALUES (gen_random_uuid(), 0, 0, NULL)
  RETURNING "Id"
)
INSERT INTO config."PowerUpDefinition" ("Id","TargetAttributeId","BoostId","MagicEffectDefinitionId","GameMapDefinitionId","MagicEffectDefinitionId1")
SELECT gen_random_uuid(), '8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06', v."Id", '9d64a001-0000-7b48-1172-c05d8158d5d4', NULL, NULL FROM v;

UPDATE config."MasterSkillDefinition"
SET "TargetAttributeId" = '8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06',
    "ValueFormula" = "ValueFormula" || ' / 100'
WHERE "Id" = '3af2a001-0000-7c83-cae0-c6571f88c52b' AND "TargetAttributeId" IS NULL;

SELECT 'classes' AS what, count(*) FROM swell_classes
UNION ALL SELECT 'relations', count(*) FROM config."AttributeRelationship" WHERE "InputAttributeId"='8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06'
UNION ALL SELECT 'consts', count(*) FROM config."ConstValueAttribute" WHERE "DefinitionId"='8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06'
UNION ALL SELECT 'powerups', count(*) FROM config."PowerUpDefinition" WHERE "TargetAttributeId"='8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06'
UNION ALL SELECT 'm363_formula', 1 FROM config."MasterSkillDefinition" WHERE "Id"='3af2a001-0000-7c83-cae0-c6571f88c52b' AND "ValueFormula" LIKE '% / 100' AND "TargetAttributeId"='8629c9cf-6a0a-4dbf-8253-54d2cd3e9a06';
COMMIT;
