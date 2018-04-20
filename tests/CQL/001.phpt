--TEST--
CommonMark\CQL firstChild
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
paragraph
EOD
);

$call = new \CommonMark\CQL("/firstChild");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Paragraph) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

