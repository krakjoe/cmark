--TEST--
CommonMark\CQL constraint List
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
  * list item
  * list item

  > block quote
EOD
);

$call = new \CommonMark\CQL("/children(List)");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\BulletList) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK

