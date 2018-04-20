--TEST--
CommonMark\CQL lastChild
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
Paragraph

> BlockQuote
EOD
);

$call = new \CommonMark\CQL("/lastChild");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\BlockQuote) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

