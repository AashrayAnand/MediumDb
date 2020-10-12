#include <gtest/gtest.h>
#include "../inc/memtable.h"
#include "../inc/kvnode.h"
#include "../inc/queryparser.h"
#include "../inc/queryexecutor.h"

TEST(TestKVNode,TestCreateNode)
{
    kvnode kvn1("foo\0", "bar\0");
    const char* expectedKey1 = "foo\0";
    const char* expectedValue1 = "bar\0";
    ASSERT_TRUE(strncmp(kvn1.Key(), expectedKey1, strlen(expectedKey1)) == 0);
    ASSERT_TRUE(strncmp(kvn1.Value(), expectedValue1, strlen(expectedValue1)) == 0);
}

TEST(TestMemTable, TestInsertNode)
{
   memtable mt;
   char* key = "foo\0";
   char* value = "bar\0";
   mt.set(key, value);
   ASSERT_TRUE(mt.Size() == 1);
   ASSERT_TRUE(mt.NumBytes() == strlen(key) + strlen(value));
}

// Verify that well formatted GET request (GET followed by key string
// of any non-zero length, null terminated) will result in query parsr
// state being set valid, and get flag being set true
TEST(TestQueryParser,TestParseGet)
{
   queryparser qp;
   qp.parse("GET foo\0");
   ASSERT_TRUE(qp.isValid());
   ASSERT_TRUE(qp.isGet());
   char* expected_key = "foo";
   ASSERT_TRUE(strncmp(qp.Key(), expected_key, strlen(expected_key)) == 0);
}

// Verify that well formatted SET request (SET folowed by key and value
// strings of non-zero length, null terminated) will result in query parser
// state being set valid, and get flag being set false
// Verify that well formatted GET request (GET followed by key string
// of any non-zero length, null terminated) will result in query parsr
// state being set valid, and get flag being set true
TEST(TestQueryParser,TestParseSet)
{
   queryparser qp;
   const char* query = "SET foo bar\0";
   qp.parse(query);
   ASSERT_TRUE(qp.isValid());
   ASSERT_TRUE(!qp.isGet());
   const char* expected_key = "foo";
   const char* expected_value = "bar";
   ASSERT_TRUE(strncmp(qp.Key(), expected_key, strlen(expected_key)) == 0);
   ASSERT_TRUE(strncmp(qp.Value(), expected_value, strlen(expected_value)) == 0);
}

// Verify that invalid input (e.g. below op with no key) will result
// in query parser state being set invalid
TEST(TestQueryParser,TestParseInvalidGet)
{
   queryparser qp;
   qp.parse("GET\0");
   ASSERT_TRUE(!qp.isValid());
}

int main(int argc, char **argv){
  
  testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}