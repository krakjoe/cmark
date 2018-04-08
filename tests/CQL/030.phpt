--TEST--
CommonMark\CQL parent(constrained)
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
> * item 1
>   * item 2
EOD
);

$call = new \CommonMark\CQL("
/firstChild(BlockQuote)[
	/firstChild(List)[
		/firstChild(Item)[
			/lastChild(List)[
				/parent(BlockQuote)
			]
		]
	]
]
");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\BlockQuote) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

