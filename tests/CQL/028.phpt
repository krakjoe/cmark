--TEST--
CommonMark\CQL next(constrained)
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
paragraph

  > block quote

  * list
EOD
);

$call = new \CommonMark\CQL("
/firstChild(Paragraph)[
  /next(List)
]
");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\BulletList) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

