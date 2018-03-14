--TEST--
CommonMark\Parse function
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOF
Title
=====

List:
  * item
  * item

[link](url "title")
EOF
);

var_dump($doc);
?>
--EXPECT--
object(CommonMark\Node\Document)#1 (1) {
  ["children"]=>
  array(4) {
    [0]=>
    object(CommonMark\Node\Heading)#2 (1) {
      ["children"]=>
      array(1) {
        [0]=>
        object(CommonMark\Node\Text)#6 (1) {
          ["literal"]=>
          string(5) "Title"
        }
      }
    }
    [1]=>
    object(CommonMark\Node\Paragraph)#3 (1) {
      ["children"]=>
      array(1) {
        [0]=>
        object(CommonMark\Node\Text)#6 (1) {
          ["literal"]=>
          string(5) "List:"
        }
      }
    }
    [2]=>
    object(CommonMark\Node\BulletList)#4 (1) {
      ["children"]=>
      array(2) {
        [0]=>
        object(CommonMark\Node\Item)#6 (1) {
          ["children"]=>
          array(1) {
            [0]=>
            object(CommonMark\Node\Paragraph)#8 (1) {
              ["children"]=>
              array(1) {
                [0]=>
                object(CommonMark\Node\Text)#9 (1) {
                  ["literal"]=>
                  string(4) "item"
                }
              }
            }
          }
        }
        [1]=>
        object(CommonMark\Node\Item)#7 (1) {
          ["children"]=>
          array(1) {
            [0]=>
            object(CommonMark\Node\Paragraph)#8 (1) {
              ["children"]=>
              array(1) {
                [0]=>
                object(CommonMark\Node\Text)#9 (1) {
                  ["literal"]=>
                  string(4) "item"
                }
              }
            }
          }
        }
      }
    }
    [3]=>
    object(CommonMark\Node\Paragraph)#5 (1) {
      ["children"]=>
      array(1) {
        [0]=>
        object(CommonMark\Node\Media\Link)#7 (3) {
          ["url"]=>
          string(3) "url"
          ["title"]=>
          string(5) "title"
          ["children"]=>
          array(1) {
            [0]=>
            object(CommonMark\Node\Text)#6 (1) {
              ["literal"]=>
              string(4) "link"
            }
          }
        }
      }
    }
  }
}

