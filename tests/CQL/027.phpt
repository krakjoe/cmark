--TEST--
CommonMark\CQL lastChild(constrained)
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
paragraph
  * item
EOD
);

$call = new \CommonMark\CQL("/lastChild(Paragraph)");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Paragraph) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

