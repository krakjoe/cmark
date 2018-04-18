--TEST--
CommonMark\CQL children constraint
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
Paragraph

> BlockQuote
EOD
);

$call = new \CommonMark\CQL("/children(Paragraph)");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Paragraph) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

