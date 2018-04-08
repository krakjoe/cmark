--TEST--
CommonMark\CQL previous(constrained)
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
paragraph

  > block quote

  * list
EOD
);

$call = new \CommonMark\CQL("
/firstChild(List)[
	/previous(Paragraph)
]
");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Paragraph) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

