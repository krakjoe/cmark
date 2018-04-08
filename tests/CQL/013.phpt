--TEST--
CommonMark\CQL constraint Item
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
  * list item
  * list item
EOD
);

$call = new \CommonMark\CQL("
/children(List)[
  /children(Item)
]
");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Item) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK
OK

